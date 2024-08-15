#ifndef LOGGER_CONFIG_HPP
#define LOGGER_CONFIG_HPP

#include <iostream>

#include <unordered_set>

#include <mutex>

#include <initializer_list>

#include "LogLevel.hpp"

/// @brief Data holder for logger thread
class LoggerConfig
{
private:
	bool print_time_relative;
	std::ostream* log_stream;
	std::unordered_set<LogLevel> ignored_log_levels;

	bool is_locked;
	static LoggerConfig* instance;

	LoggerConfig();
public:
	static LoggerConfig* getInstance();

	LoggerConfig* setIfTimeRelative(bool value) { this->print_time_relative = value; return this; }
	LoggerConfig* ignoreLevels(std::initializer_list<LogLevel> levels) { 
		for (LogLevel level : levels)
			this->ignored_log_levels.insert(level);
		return this;
	}


	inline std::ostream* getLogStream() const { return this->log_stream; }
	inline bool isPrintingTimeRelative() const { return this->print_time_relative; }
	inline const std::unordered_set<LogLevel>& getIgnoredLevels() const { return this->ignored_log_levels; }

	inline void lock() { this->is_locked = true; }
};


#endif //!LOGGER_CONFIG_HPP