#ifndef LOG_MESSAGE_HPP
#define LOG_MESSAGE_HPP

#ifndef EXECUTABLE_NAME
#define EXECUTABLE_NAME "UNKNOWN"
#endif // !EXECUTABLE_NAME

#include <string>
#include <chrono>

#include "LogLevel.hpp"

using std::chrono::high_resolution_clock;

/// @brief Simple class to represent a log message
class LogMessage {
	public:
		std::string message;
		std::string path;
		LogLevel level;
		high_resolution_clock::time_point timestamp;
		LogMessage(
			std::string, 
			std::string = "", 
			LogLevel = LogLevel::INFO);		
		~LogMessage() {}

};

#endif //!LOG_MESSAGE_HPP