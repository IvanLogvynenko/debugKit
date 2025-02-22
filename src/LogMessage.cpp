#include "LogMessage.hpp"

namespace Logger {
LogMessage::LogMessage(std::string message, std::string path, LogLevel level)
    : message(message), path(path), level(level), timestamp(high_resolution_clock::now()) {}
} // namespace Logger
