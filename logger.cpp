#include "logger.h"
#include <exception>


void Logger::set_strategy(std::unique_ptr<LoggerStrategy> new_strategy) {
    strategy = std::move(new_strategy);
}

void Logger::log_message(const std::string &message) {
    if (strategy) {
        strategy->write(message);
    } else {
        throw std::runtime_error("Logger strategy not set!");
    }
}    