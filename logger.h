#include "loggerstrategy.h"
#include <memory>
#include <string>

class Logger {
private:
    std::unique_ptr<LoggerStrategy> strategy;
public:
    void set_strategy(std::unique_ptr<LoggerStrategy> new_strategy);

    void log_message(const std::string &message);
};