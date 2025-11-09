#ifndef ELDERGLYPH_MENU_H
#define ELDERGLYPH_MENU_H

#include "../gameengine/GameEngine.h"
#include "../console/ui/ConsoleUI.h"
#include "../logger/LoggerMacros.h"
#include "MenuConstants.h"
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

public:
    static Menu& getInstance();

    static void showMenu();

    Menu(const Menu&) = delete;

    Menu& operator=(const Menu&) = delete;

    Menu(Menu&&) = delete;

    Menu& operator=(Menu&&) = delete;
};

#endif // ELDERGLYPH_MENU_H
