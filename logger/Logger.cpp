#include "Logger.h"

Logger::Logger()
{
    std::filesystem::create_directories("logs");

    archiveLogFile();

    logFile_.open("logs/latest.log", std::ios_base::app);
    if (!logFile_.is_open())
    {
        std::cerr << RED_NORMAL_TEXT << "Unable to open log file!" << RESET_TEXT << "\n";
    }
}

Logger::~Logger()
{
    if (logFile_.is_open())
    {
        logFile_.close();
    }
}

Logger& Logger::getInstance()
{
    static Logger instance;
    return instance;
}

void Logger::showLog()
{
#ifdef _WIN32

    const std::string logFilePath = "logs\\latest.log";

    if (!std::filesystem::exists(logFilePath))
    {
        std::cerr << RED_NORMAL_TEXT << "Log file not found: " << logFilePath << RESET_TEXT << "\n";
        return;
    }

    const std::string command = "notepad.exe \"" + logFilePath + "\"";

    STARTUPINFOA si = {sizeof(STARTUPINFOA)};
    PROCESS_INFORMATION pi;

    if (!CreateProcessA(nullptr, const_cast<char*>(command.c_str()), nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si,
                        &pi))
    {
        std::cerr << RED_NORMAL_TEXT << "CreateProcess failed (" << GetLastError() << ")." << RESET_TEXT << "\n";
        return;
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
#else

    std::cerr << RED_NORMAL_TEXT << "Log file viewer is only supported on Windows." << RESET_TEXT << "\n";
#endif
}

void Logger::log(const LogLevel type, const std::string& message) {
    std::lock_guard lock(logMutex_);

    if (logFile_.is_open()) {
        logFile_ << formatLogMessage(type, message) << std::endl;
    } else {
        std::cerr << "Unable to open log file!" << RESET_TEXT << std::endl;
    }
}

std::string Logger::formatLogMessage(const LogLevel type, const std::string& message)
{
    std::ostringstream oss;
    oss << "[" << logLevelToString(type) << ": " << getCurrentTime() << "] " << message;
    return oss.str();
}

std::string Logger::logLevelToString(const LogLevel type)
{
    switch (type)
    {
    case Info:
        return "Info";
    case Error:
        return "Error";
    case Warning:
        return "Warning";
    default:
        return "Unknown";
    }
}

std::string Logger::getCurrentTime()
{
    std::lock_guard lock(logMutex_);

    const auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::tm local_tm{};
#ifdef _WIN32

    localtime_s(&local_tm, &in_time_t);
#else

    localtime_r(&in_time_t, &local_tm);
#endif

    const auto ms = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()) % 1000000;

    std::ostringstream oss;
    oss << std::put_time(&local_tm, "%Y-%m-%d %H:%M:%S");
    oss << '.' << std::setw(6) << std::setfill('0') << ms.count();
    return oss.str();
}

void Logger::archiveLogFile()
{
    std::lock_guard lock(logMutex_);

    if (const std::string logFilePath = "logs/latest.log"; std::filesystem::exists(logFilePath))
    {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        std::tm local_tm{};
#ifdef _WIN32
        localtime_s(&local_tm, &in_time_t);
#else
        localtime_r(&in_time_t, &local_tm);
#endif

        std::ostringstream date_oss;
        date_oss << std::put_time(&local_tm, "%Y-%m-%d");
        std::string date_str = date_oss.str();

        int sequence_number = 1;
        std::string newLogFileName;

        do
        {
            std::ostringstream new_oss;
            new_oss << "logs/" << "log-" << date_str << "-" << sequence_number << ".log";
            newLogFileName = new_oss.str();
            sequence_number++;
        }
        while (std::filesystem::exists(newLogFileName));

        std::filesystem::rename(logFilePath, newLogFileName);
    }
}
