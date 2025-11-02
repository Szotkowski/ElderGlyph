#ifndef ELDERGLYPH_LOGGERMACROS_H
#define ELDERGLYPH_LOGGERMACROS_H

#include "Logger.h"

#define LOG_INFO(message) Logger::getInstance().log(LogLevel::Info, message)
#define LOG_ERROR(message) Logger::getInstance().log(LogLevel::Error, message)
#define LOG_WARNING(message) Logger::getInstance().log(LogLevel::Warning, message)

#endif // ELDERGLYPH_LOGGERMACROS_H
