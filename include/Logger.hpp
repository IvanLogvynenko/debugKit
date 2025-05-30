#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>

#include <sstream>

#include "LoggerThread.hpp"

namespace Logger {
class Logger {
protected:
    LogLevel current_level;
    std::string path;

    std::ostringstream buffer;

    LoggerThread *logger_thread;

public:
    Logger(std::string = "");
    Logger(Logger &);
    Logger &operator=(const Logger &);
    ~Logger();

    static void flush() { LoggerThread::getInstance()->flush(); }

    template <typename T> Logger &operator<<(const T &value) {
        buffer << value;
        return *this;
        // forced to provide an implementation here because it is templete function
    }
    Logger &operator<<(std::ostream &(*) (std::ostream &) );
    inline Logger &operator<<(Logger *(*function)(Logger *) ) { return *function(this); }

    inline void setLevel(LogLevel new_level) { current_level = new_level; }
    inline LogLevel getLevel() const { return current_level; }
    inline std::string getPath() const { return path; }
};

Logger *debug(Logger *);
Logger *info(Logger *);
Logger *important(Logger *);
Logger *warning(Logger *);
Logger *error(Logger *);
Logger *critical(Logger *);
} // namespace Logger
#endif //! LOGGER_HPP

using Logger::critical;
using Logger::debug;
using Logger::error;
using Logger::important;
using Logger::info;
using Logger::warning;
