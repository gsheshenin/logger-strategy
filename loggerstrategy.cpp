#include "loggerstrategy.h"

void ConsoleLogger::write(const std::string &message) {
    std::cout << message << std::endl;
}

void SimpleFileLogger::write(const std::string &message) {
    file << message << std::endl;
}

void TimedFileLogger::write(const std::string &message) {
    std::time_t now = std::time(nullptr);
    std::tm *tm_now = std::localtime(&now);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_now);
    file << "[" << buffer << "] " << message << std::endl;
}