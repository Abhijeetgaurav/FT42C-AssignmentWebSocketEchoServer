#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <mutex>
#include <iostream>

//Logger class implementing a singleton pattern
class Logger {
private:
    std::mutex mutex_;
    Logger() = default;
public:
    //static method so that single instance can only be created
    static Logger& instance();
    //method for log messages
    void log(const std::string& message);

};

#endif // LOGGER_H
