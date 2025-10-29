#ifndef ELDERGLYPH_MENU_H
#define ELDERGLYPH_MENU_H

#include "GameEngine.h"
#include "logger/Logger.h"
#include "AnsiCodes.h"
#include "MenuTypes.h"
#include "MenuConstants.h"

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#endif

class Menu
{
private:
    Menu();

    ~Menu();

    static void drawOption(const std::string& option, int width, MenuTypes::OptionIndex index, int currentIndex);

    static void drawHorizontalBorder(int width, bool isEndOfWindow = false);

    static void drawEmptyFrameLine(int width, int count);

    static void drawTitle(int consoleWidth);

    static void drawFullMenu(int consoleWidth, int consoleHeight, int currentIndex);

    static void handleOptionSelection(MenuTypes::OptionIndex option);

    static void handleInput(int& currentIndex, bool& shouldRedraw);

public:
    static Menu& getInstance();

    static void showMenu();

    Menu(const Menu&) = delete;

    Menu& operator=(const Menu&) = delete;

    Menu(Menu&&) = delete;

    Menu& operator=(Menu&&) = delete;
};

#endif // ELDERGLYPH_MENU_H
