#include <fstream>
#include <iostream>
#include <ctime>


class LoggerStrategy {
public:
    virtual void write(const std::string &message) = 0;
    virtual ~LoggerStrategy() = default;
};

class ConsoleLogger : public LoggerStrategy {
public:
    void write(const std::string &message) override;
};

class SimpleFileLogger : public LoggerStrategy {
private:
    std::ofstream file;
public:
    SimpleFileLogger(const std::string &filename) {
        file.open(filename, std::ios::app);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file for logging");
        }
    }

    void write(const std::string &message) override;
    ~SimpleFileLogger() {
        if (file.is_open()) {
            file.close();
        }
    }
};

class TimedFileLogger : public LoggerStrategy {
private:
    std::ofstream file;
public:
    TimedFileLogger(const std::string &filename) {
        file.open(filename, std::ios::app);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file for logging");
        }
    }

    void write(const std::string &message) override;

    ~TimedFileLogger() {
        if (file.is_open()) {
            file.close();
        }
    }
};