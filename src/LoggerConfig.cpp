#include "LoggerConfig.hpp"

LoggerConfig* LoggerConfig::instance = nullptr;
LoggerConfig* LoggerConfig::getInstance() {
	if (instance == nullptr) {
        instance = new LoggerConfig();
    }
    return instance;
}

LoggerConfig::LoggerConfig() :
	log_stream(&std::cout),
	ignored_log_levels(),
	print_time_relative(false) {}