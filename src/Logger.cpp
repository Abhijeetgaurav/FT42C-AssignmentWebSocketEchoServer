#include "Logger.h"

// defining the logger creating instance
Logger& Logger::instance() {
    static Logger logger;
    return logger;
}

// defining the log method for printing messages
void Logger::log(const std::string& message) {
    //prevent the race condition and thread safety
    std::lock_guard<std::mutex> lock(mutex_);
    //diaplaying the message
    std::cout << message << std::endl;
}
