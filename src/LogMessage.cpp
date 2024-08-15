#include "LogMessage.hpp"

LogMessage::LogMessage(std::string message, std::string path, LogLevel level) :
	message(std::move(message)),
	path(std::move(path)),
	level(std::move(level)),
	timestamp(high_resolution_clock::now()) {}

