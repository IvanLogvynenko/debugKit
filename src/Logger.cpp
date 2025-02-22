#include "Logger.hpp"

namespace Logger {
Logger *debug(Logger *logger) {
    logger->setLevel(LogLevel::DEBUG);
    return logger;
}
Logger *info(Logger *logger) {
    logger->setLevel(LogLevel::INFO);
    return logger;
}
Logger *important(Logger *logger) {
    logger->setLevel(LogLevel::IMPORTANT);
    return logger;
}
Logger *warning(Logger *logger) {
    logger->setLevel(LogLevel::WARNING);
    return logger;
}
Logger *error(Logger *logger) {
    logger->setLevel(LogLevel::ERROR);
    return logger;
}
Logger *critical(Logger *logger) {
    logger->setLevel(LogLevel::CRITICAL);
    return logger;
}

Logger::Logger(std::string path) : current_level(LogLevel::INFO), logger_thread(LoggerThread::getInstance()) {
    logger_thread->awaitStart();

    if (path != "") { this->path = " " + path; }
}
Logger::Logger(Logger &other) {
    if (this == &other) { return; }

    this->current_level = other.current_level;
    this->path = other.path;
    this->buffer.str(other.buffer.str());
}
Logger &Logger::operator=(const Logger &other) {
    if (this == &other) { return *this; }

    this->current_level = other.current_level;
    this->path = other.path;
    this->buffer.str(other.buffer.str());
    return *this;
}

Logger &Logger::operator<<(std::ostream &(*func)(std::ostream &) ) {
    if (func == static_cast<std::ostream &(*) (std::ostream &)>(&std::endl)) {
        this->buffer << "\n";
        LogMessage *message = new LogMessage(this->buffer.str(), this->path, this->current_level);
        this->logger_thread->log(message);
        this->buffer.str(std::string());
        this->current_level = LogLevel::INFO;
        return *this;
    }
    this->buffer << func;
    return *this;
}

Logger::~Logger() {
    // if there is still something in the buffer, log it
    //  std::cout << "Logger destroyed" << std::endl;
    if (this->buffer.str() != "") { *this << std::endl; }

    this->buffer.str(std::string());
    this->buffer.flush();
}
} // namespace Logger