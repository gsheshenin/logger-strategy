#include "logger.h"


int main() {
    Logger logger;

    logger.set_strategy(std::make_unique<ConsoleLogger>());
    logger.log_message("This is a message to the console.");

    logger.set_strategy(std::make_unique<SimpleFileLogger>("log.txt"));
    logger.log_message("This is a message to the file.");

    logger.set_strategy(std::make_unique<TimedFileLogger>("timed_log.txt"));
    logger.log_message("This is a timed message to the file.");

    return 0;
}