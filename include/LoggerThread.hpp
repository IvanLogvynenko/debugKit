#ifndef LOGGER_THREAD_HPP
#define LOGGER_THREAD_HPP

#ifndef LOGGER_THREAD_IDLE_TIMEOUT
#define LOGGER_THREAD_IDLE_TIMEOUT 10000  // 10 seconds
#endif // !LOGGER_THREAD_IDLE_TIMEOUT

#include <iostream>

#include <string>
#include <chrono>
using namespace std::chrono;
#include <iomanip>

#include <queue>
#include <sstream>

#include <mutex>
#include <atomic>
#include <thread>
#include <condition_variable>

#include "LogLevel.hpp"
#include "LogMessage.hpp"
#include "LoggerConfig.hpp"

class LoggerThread
{
private:
	std::mutex log_queue_mutex;
	std::queue<LogMessage*> log_queue;

	std::thread* main_thread;

    std::mutex new_data_available_mutex;
	std::condition_variable new_data_available;

	std::atomic_bool is_initialized;
	std::mutex is_initialized_mutex;
    std::condition_variable cv_initialized;

	static LoggerThread* instance;

	LoggerThread();

	std::string getStringLevel(LogLevel level) const;
	std::string getStringTimestamp(high_resolution_clock::time_point) const;

	std::string printLog(LogMessage*) const;
public:
    LoggerThread(LoggerThread&) = delete;
	LoggerThread& operator=(LoggerThread&) = delete;

	~LoggerThread();

	static LoggerThread* getInstance();

	void log(LogMessage*);
};


#endif // !LOGGER_THREAD_HPP