#include "Menu.h"
#include "logger/Logger.h"
#include "ConsoleInitializer.h"

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
        return 1;
    }
#endif

    Menu::showMenu();

    LOG_INFO("Game exited successfully.");
    return 0;
}
