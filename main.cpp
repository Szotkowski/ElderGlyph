#include "console/core/ConsoleInitializer.h"
#include "logger/LoggerMacros.h"
#include "menu/Menu.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main()
{
    LOG_INFO("Starting game...");

#ifdef _WIN32
    SetConsoleTitle("ElderGlyph");
    if (!Console::initialize())
    {
        LOG_ERROR("Failed to initialize Windows console.");
        return 1;
    }
#endif

    Menu::showMenu();

    LOG_INFO("Game exited successfully.");
    return 0;
}
