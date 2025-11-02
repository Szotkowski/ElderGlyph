#ifndef ELDERGLYPH_MENU_H
#define ELDERGLYPH_MENU_H

#include "../gameengine/GameEngine.h"
#include "../logger/LoggerMacros.h"
#include "../console/ConsoleUI.h"
#include "../console/Console.h"
#include "../logger/Logger.h"
#include "MenuConstants.h"
#include "../AnsiCodes.h"
#include "MenuTypes.h"

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#endif

class Menu
{
private:
    Menu();

    ~Menu();

    static void drawFullMenu(int currentIndex);

    static void handleOptionSelection(MenuTypes::OptionIndex option);

public:
    static Menu& getInstance();

    static void showMenu();

    Menu(const Menu&) = delete;

    Menu& operator=(const Menu&) = delete;

    Menu(Menu&&) = delete;

    Menu& operator=(Menu&&) = delete;
};

#endif // ELDERGLYPH_MENU_H
