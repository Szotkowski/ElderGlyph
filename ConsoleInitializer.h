#ifndef ELDERGLYPH_CONSOLEINITIALIZER_H
#define ELDERGLYPH_CONSOLEINITIALIZER_H

#include "logger/Logger.h"
#include "AnsiCodes.h"

#ifdef _WIN32
namespace Console
{
    bool initialize();
}
#endif // _WIN32

#endif // ELDERGLYPH_CONSOLEINITIALIZER_H
