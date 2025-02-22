#ifndef LOGGER_CONFIG_HPP
#define LOGGER_CONFIG_HPP

#include <fstream>
#include <iostream>

#include <unordered_set>

#include <mutex>

#include <initializer_list>

#include "LogLevel.hpp"
#include "LoggerThread.hpp"

namespace Logger {
/// @brief Data holder for logger thread
class LoggerConfig {
private:
    std::ostream *log_stream;
    std::unordered_set<LogLevel> ignored_log_levels;
    std::string executable_name = "UNKNOWN";

    bool is_locked;

    LoggerConfig();

public:
    static LoggerConfig *getInstance();
    ~LoggerConfig();

    LoggerConfig *ignoreLevels(std::initializer_list<LogLevel> levels);
    LoggerConfig *setLogStream(std::ostream *stream);
    LoggerConfig *logToFile(const std::string &file_path);
    LoggerConfig *setExecutableName(const char *name);

    inline const std::unordered_set<LogLevel> &getIgnoredLevels() const { return this->ignored_log_levels; }
    inline std::ostream *getLogStream() const { return this->log_stream; }
    inline const std::string &getExecutableName() const { return this->executable_name; }

    inline void lock() { this->is_locked = true; }
};
} // namespace Logger

#endif //! LOGGER_CONFIG_HPP