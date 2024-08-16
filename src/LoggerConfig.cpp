#include "LoggerConfig.hpp"

LoggerConfig* LoggerConfig::getInstance() {
	static LoggerConfig instance;
    return &instance;
}

LoggerConfig::LoggerConfig() :
	log_stream(&std::cout),
	ignored_log_levels() {}


LoggerConfig *LoggerConfig::setLogStream(std::ostream *stream) {
	if (is_locked) throw std::runtime_error("Logger can be configured only before Logging is started");
	log_stream = stream;
	return this;
}
LoggerConfig *LoggerConfig::ignoreLevels(std::initializer_list<LogLevel> levels) {
	if (is_locked) throw std::runtime_error("Logger can be configured only before Logging is started");
	for (LogLevel level : levels)
		this->ignored_log_levels.insert(level);
	return this;
}
LoggerConfig *LoggerConfig::logToFile(const std::string &file_path) {
	if (is_locked) throw std::runtime_error("Logger can be configured only before Logging is started");
    if (log_stream!= &std::cout) {
        delete log_stream;
    }
    auto new_stream = new std::ofstream(file_path);
	if (!new_stream->is_open()) 
		throw std::runtime_error("Failed to open log file: " + file_path);

	log_stream = new_stream;
	return this;
}



LoggerConfig::~LoggerConfig() {
	if (log_stream != &std::cout) {
		*log_stream << std::endl;
		log_stream->flush();
		delete log_stream;
	}
}
