#ifndef LOGGER_H
#define LOGGER_H

#include "LoggerTypes.h"
#include "../AnsiCodes.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <filesystem>
#include <windows.h>
#include <mutex>

class Logger {
private:
    Logger();

    ~Logger();

    std::ofstream logFile_;

    std::recursive_mutex logMutex_;

    std::string formatLogMessage(LogLevel type, const std::string &message);

    static std::string logLevelToString(LogLevel type);

    std::string getCurrentTime();

    void archiveLogFile();

public:
    static Logger &getInstance();

    static void showLog();

    void log(LogLevel type, const std::string &message);

    Logger(const Logger &) = delete;

    Logger &operator=(const Logger &) = delete;

    Logger(Logger &&) = delete;

    Logger &operator=(Logger &&) = delete;
};

#endif //LOGGER_H
