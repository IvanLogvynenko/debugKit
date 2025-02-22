#ifndef LOGGER_THREAD_HPP
#define LOGGER_THREAD_HPP

#ifndef LOGGER_THREAD_IDLE_TIMEOUT
#define LOGGER_THREAD_IDLE_TIMEOUT 10000 // 10 seconds
#endif // !LOGGER_THREAD_IDLE_TIMEOUT

#ifndef LOGGER_THREAD_START_TIMEOUT
#define LOGGER_THREAD_START_TIMEOUT 5 // 5 miliseconds
#endif // !LOGGER_THREAD_START_TIMEOUT

#ifndef EXECUTABLE_NAME
#define EXECUTABLE_NAME "UNKNOWN"
#endif // !EXECUTABLE_NAME

#include <iostream>

#include <chrono>
#include <string>
using namespace std::chrono;
#include <iomanip>

#include <queue>
#include <sstream>

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>

#include "LogLevel.hpp"
#include "LogMessage.hpp"
#include "LoggerConfig.hpp"

namespace Logger {
class LoggerThread {
private:
    std::mutex log_queue_mutex;
    std::queue<LogMessage *> log_queue;

    std::atomic<std::thread *> main_thread;

    std::mutex new_data_available_mutex;
    std::condition_variable new_data_available;

    // one to stop thread, one to indicate if thread is running and one ring to rule them all
    std::atomic_bool stop_thread;
    std::atomic_bool is_running;

    std::mutex log_thread_started_mutex;
    std::condition_variable log_thread_started;

    LoggerThread();

    void startThread();

    std::string getStringLevel(LogLevel level) const;
    std::string getStringTimestamp(high_resolution_clock::time_point) const;

    std::string printLog(LogMessage *) const;

public:
    LoggerThread(LoggerThread &) = delete;
    LoggerThread &operator=(LoggerThread &) = delete;

    void awaitStart();

    void flush();
    ~LoggerThread();

    static LoggerThread *getInstance();

    void log(LogMessage *);
};
} // namespace Logger

#endif // !LOGGER_THREAD_HPP