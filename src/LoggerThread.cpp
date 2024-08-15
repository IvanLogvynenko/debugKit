#include "LoggerThread.hpp"

LoggerThread::LoggerThread() : is_running(false) {
	auto conf = LoggerConfig::getInstance();
	this->main_thread = new std::thread([this, conf]() {
		is_running = true;
		while (is_running || !this->log_queue.empty()) {
			std::cout << "new iteration" << std::endl;
			std::cout << "checking queue size: " << this->log_queue.size() << std::endl;
			if (this->log_queue.empty()) {
				// waiting logic. if no new log available, wait for a while and then check again
				// if none found stop thread

                std::cout << "No new log available, waiting for " << LOGGER_THREAD_IDLE_TIMEOUT << std::endl;
				std::unique_lock<std::mutex> cv_lock(this->new_data_available_mutex);
				std::cv_status result = this->new_data_available.wait_for(cv_lock, std::chrono::milliseconds(LOGGER_THREAD_IDLE_TIMEOUT));

				std::cout << "waiting ended" << std::endl;
				if (result == std::cv_status::timeout) {
					std::cout << "Timeout reached, exiting thread" << std::endl;
					is_running = !this->log_queue.empty();
					continue;
				    // if () {
					// 	std::cout << "No new log available and timeout reached, exiting thread" << std::endl;
					// }
					// else {
					// 	std::cout << "New log available, continuing iteration" << std::endl;
					// 	continue;
					// }
				}
				else {
					std::cout << "New log available, continuing iteration" << std::endl;
					// continue;
				}
			}
			std::unique_lock<std::mutex> queue_lock(this->log_queue_mutex);
			LogMessage* message = this->log_queue.front();
			std::cout << "Processing log: " << message->message << std::endl;
			this->log_queue.pop();
			queue_lock.unlock();
			// skipping if log level is ignored
			if (conf->getIgnoredLevels().find(message->level) == conf->getIgnoredLevels().end())
				*conf->getLogStream() << this->printLog(message);
			
			delete message;
		}
	});
	std::cout << "LoggerThread started " << main_thread << std::endl;
}



LoggerThread *LoggerThread::getInstance() {
	static LoggerThread instance;
	return &instance;
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

	std::unique_lock<std::mutex> queue_lock(this->log_queue_mutex);
    this->log_queue.push(message);
	queue_lock.unlock();

    this->new_data_available.notify_all();
	std::cout << "new log added to queue" << std::endl;
}



LoggerThread::~LoggerThread() {
	std::cout << "LoggerThread destructor" << std::endl;

    std::cout << "stoping LoggerThread " << main_thread << std::endl;
	if (this->main_thread != nullptr) 
	    this->main_thread->join();

	delete this->main_thread;
	this->main_thread = nullptr;
	std::cout << "LoggerThread destroyed" << std::endl;
}