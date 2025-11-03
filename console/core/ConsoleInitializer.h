#ifndef ELDERGLYPH_CONSOLEINITIALIZER_H
#define ELDERGLYPH_CONSOLEINITIALIZER_H

#include "../../logger/LoggerMacros.h"
#include "Console.h"

#ifdef _WIN32
#include <windows.h>

namespace Console
{
    bool initialize();
}
#endif // _WIN32

#endif // ELDERGLYPH_CONSOLEINITIALIZER_H
