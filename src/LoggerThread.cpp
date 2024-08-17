#include "LoggerThread.hpp"

LoggerThread::LoggerThread() : 
	stop_thread(true),
	is_running(false)
	{}
void LoggerThread::startThread() {
	if (this->is_running) return;
	this->main_thread = new std::thread([this]() {
		auto conf = LoggerConfig::getInstance();
		conf->lock();
		auto stream = conf->getLogStream();

		this->is_running = true;
		this->stop_thread = false;
		this->log_thread_started.notify_all();

		while (!this->stop_thread || !this->log_queue.empty()) {
			if (this->log_queue.empty()) {
				std::unique_lock<std::mutex> cv_lock(this->new_data_available_mutex);
				std::cv_status result = this->new_data_available.wait_for(cv_lock, std::chrono::milliseconds(LOGGER_THREAD_IDLE_TIMEOUT));

				if (result == std::cv_status::timeout) {
					this->stop_thread = this->log_queue.empty();
					continue;
				}
			}

			std::unique_lock<std::mutex> queue_lock(this->log_queue_mutex);
			LogMessage* message = this->log_queue.front();
			this->log_queue.pop();

			queue_lock.unlock();
			if (conf->getIgnoredLevels().find(message->level) == conf->getIgnoredLevels().end())
				*stream << this->printLog(message);
			
			delete message;
		}
		this->stop_thread = true;
		this->is_running = false;
	});
}



void LoggerThread::awaitStart() {
	if (this->is_running) return;
	std::unique_lock<std::mutex> cv_lock(this->log_thread_started_mutex);
	this->log_thread_started.wait_for(cv_lock, std::chrono::milliseconds(LOGGER_THREAD_START_TIMEOUT));
}



LoggerThread *LoggerThread::getInstance() {
	static LoggerThread instance;
	return &instance;
}



std::string LoggerThread::getStringLevel(LogLevel level) const
{
	switch (level)
	{
		case LogLevel::CRITICAL: 	return "CRITICAL ";
		case LogLevel::ERROR: 		return "  ERROR  ";
		case LogLevel::DEBUG: 		return "  DEBUG  ";
		case LogLevel::INFO: 		return "   INFO  ";
		case LogLevel::IMPORTANT: 	return "IMPORTANT";
		case LogLevel::WARNING: 	return " WARNING ";
		default: 					return " UNKNOWN ";
	}
}
std::string LoggerThread::getStringTimestamp(high_resolution_clock::time_point timepoint) const
{
	auto time_t_timestamp = std::chrono::system_clock::to_time_t(timepoint);
	
	std::tm* tm_time = std::localtime(&time_t_timestamp);
	auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(timepoint.time_since_epoch()) % 1000;	// auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(timepoint.time_since_epoch()) / 1000;

	std::ostringstream oss;
	oss << std::put_time(tm_time, "%Y-%m-%d %H:%M:%S");
	oss << '.' << std::setw(3) << std::setfill('0') << milliseconds.count() << "ms";
	// oss << timepoint.time_since_epoch().count();

	return oss.str();
}
std::string LoggerThread::printLog(LogMessage* message) const
{
	std::stringstream ss;
	ss << "[ " << this->getStringLevel(message->level) 								<< " ]";
	ss << "[ " << this->getStringTimestamp(message->timestamp) 						<< " ]";
	ss << "[ " << LoggerConfig::getInstance()->getExecutableName() << message->path << " ]\n";
	ss << ">>> " << message->message;
    return ss.str();
}



void LoggerThread::log(LogMessage* message) {
	// std::cout << "new log" << std::endl;
	if (!this->is_running) {
	    this->startThread();
		this->awaitStart();
	}

	std::unique_lock<std::mutex> queue_lock(this->log_queue_mutex);
    this->log_queue.push(message);
	queue_lock.unlock();

    this->new_data_available.notify_all();
	// std::cout << "new log added to queue" << std::endl;
}



LoggerThread::~LoggerThread() {
	this->stop_thread = true;
	this->new_data_available.notify_all();

	if (this->main_thread != nullptr) {
		this->main_thread->join();

		delete this->main_thread;
		this->main_thread = nullptr;
	}
}