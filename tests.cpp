#include <gtest/gtest.h>
#include "logger.h"
#include <cstdio>
#include <iostream>


TEST(ConsoleLoggerTest, WriteMessage) {
    Logger logger;
    testing::internal::CaptureStdout();
    logger.set_strategy(std::make_unique<ConsoleLogger>());
    logger.log_message("console log");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "console log\n");

}

TEST(SimpleFileLoggerTest, WriteMessage) {
    Logger logger;
    FILE* file = fopen("log.txt", "r");
    if(file){
        fclose(file);
        remove("log.txt");
    }
    logger.set_strategy(std::make_unique<SimpleFileLogger>("log.txt"));
    logger.log_message("file log");
    std::fstream input("log.txt");
    std::string line;
    std::getline(input, line);
    EXPECT_EQ(line, "file log");
    input.close();
}

TEST(TimedFileLoggerTest, WriteMessage) {
    std::time_t now = std::time(nullptr);
    std::tm *tm_now = std::localtime(&now);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_now);
    Logger logger;
    FILE* file = fopen("timed_log.txt", "r");
    if(file){
        fclose(file);
        remove("timed_log.txt");
    }
    logger.set_strategy(std::make_unique<TimedFileLogger>("timed_log.txt"));
    logger.log_message("file log with time");
    std::fstream input("timed_log.txt");
    std::string line;
    std::getline(input, line);
    std::string buf(buffer);
    std::string res = "[" + buf + "] file log with time";
    EXPECT_EQ(line, res);
    input.close();
}

TEST(LoggerTest, LogMessageWithoutStrategy) {
    Logger logger;
    try{
        logger.log_message("This should not log");
    }
    catch(const std::runtime_error& e) {
        EXPECT_EQ(std::string(e.what()), "Logger strategy not set!");
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}