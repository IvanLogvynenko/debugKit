#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>

#include <sstream>

#include <functional>

#include "LoggerThread.hpp"

class Logger
{
protected:
	LogLevel current_level;
	std::string path;

	std::ostringstream buffer;

	LoggerThread* logger_thread;
public:
	Logger(std::string = "");
    Logger(Logger&);
	Logger& operator=(const Logger&);
	~Logger();

	static Logger* debug(Logger*);
	static Logger* info(Logger*);
	static Logger* important(Logger*);
	static Logger* warning(Logger*);
	static Logger* error(Logger*);
	static Logger* critical(Logger*);

	template <typename T>
    Logger& operator<<(const T& value) {
        buffer << value;
        return *this;
		// forced to provide an implementation here because it is templete function
    }
	Logger& operator<<(std::ostream&(*)(std::ostream&));
	inline Logger& operator<<(Logger*(*function)(Logger*)) { return *function(this); }

	inline void setLevel(LogLevel new_level) { current_level = new_level; }
	inline LogLevel getLevel() const { return current_level; }
	inline std::string getPath() const { return path; }
};

#endif //!LOGGER_HPP