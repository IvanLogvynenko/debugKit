#include "LoggerThread.hpp"

LoggerThread *LoggerThread::instance = nullptr;

LoggerThread::LoggerThread() : is_initialized(false) {
	auto conf = LoggerConfig::getInstance();
	this->main_thread = new std::thread([this, conf]() {
		while (true) {
			std::lock_guard<std::mutex> queue_lock(this->log_queue_mutex);
			if (this->log_queue.empty()) {

				// waiting logic. if no new log available, wait for a while and then check again
				// if none found stop thread

				std::unique_lock<std::mutex> cv_lock(this->new_data_available_mutex);
				std::cv_status result = this->new_data_available.wait_for(cv_lock, std::chrono::milliseconds(LOGGER_THREAD_IDLE_TIMEOUT));

				if (result == std::cv_status::timeout)
				    if (this->log_queue.empty()) break;
					else continue;
				else continue;
			}
			
			LogMessage* message = this->log_queue.front();
			this->log_queue.pop();

			// skipping if log level is ignored
			if (conf->getIgnoredLevels().find(message->level) == conf->getIgnoredLevels().end())
				*conf->getLogStream() << this->printLog(message);
			
			delete message;
		}
		delete instance;
		instance = nullptr;
	});
}



LoggerThread *LoggerThread::getInstance() {
	if (instance == nullptr) 
		instance = new LoggerThread();
	return instance;
}



std::string LoggerThread::getStringLevel(LogLevel level) const
{
	switch (level)
	{
		case LogLevel::CRITICAL: return "CRITICAL";
		case LogLevel::ERROR: return "ERROR";
		case LogLevel::DEBUG: return "DEBUG";
		case LogLevel::INFO: return "INFO";
		case LogLevel::IMPORTANT: return "IMPORTANT";
		case LogLevel::WARNING: return "WARNING";
		default: return "UNKNOWN";
	}
}
std::string LoggerThread::getStringTimestamp(high_resolution_clock::time_point) const
{
	auto time_t_timestamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    
    std::tm* tm_time = std::localtime(&time_t_timestamp);

    std::ostringstream oss;
    oss << std::put_time(tm_time, "%Y-%m-%d %H:%M:%S");

    return oss.str();
}
std::string LoggerThread::printLog(LogMessage* message) const
{
	std::stringstream ss;
	ss << " [ " << this->getStringLevel(message->level) 			<< " ] ";
	ss << " [ " << EXECUTABLE_NAME << message->path 				<< " ] ";
	ss << " [ " << this->getStringTimestamp(message->timestamp) 	<< " ] ";
	ss << " >>> " << message->message;
    return ss.str();
}



void LoggerThread::log(LogMessage* message) {
	std::cout << "new log" << std::endl;
	std::lock_guard<std::mutex> queue_lock(this->log_queue_mutex);
    this->log_queue.push(message);
	std::unique_lock<std::mutex> cv_lock(this->new_data_available_mutex);
    this->new_data_available.notify_all();
}



LoggerThread::~LoggerThread() {
	if (this->main_thread != nullptr) 
	    this->main_thread->join();

	delete this->main_thread;
	this->main_thread = nullptr;
	std::cout << "LoggerThread destroyed" << std::endl;
}