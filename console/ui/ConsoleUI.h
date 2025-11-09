#ifndef ELDERGLYPH_CONSOLEUI_H
#define ELDERGLYPH_CONSOLEUI_H

#include "ConsoleUIConstants.h"
#include "../../AnsiCodes.h"
#include "../core/Console.h"
#include "../../KeyCodes.h"
#include <string_view>
#include <functional>
#include <iostream>
#include <iomanip>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#endif

namespace ConsoleUI
{
    void drawHorizontalBorder(int width, bool isEndOfWindow = false);

    void drawEmptyFrameLine(int width, int count);

    void drawCenteredOption(int width, std::string_view option, bool isSelected,
                            std::string_view selectedColor, std::string_view resetColor);

    void drawCenteredArt(int consoleWidth, std::size_t artWidth,
                         const std::vector<std::string_view>& artLines,
                         std::string_view artColor, std::string_view resetColor);

    void drawFrameContent(
        const std::vector<std::string_view>& artLines,
        std::size_t artWidth,
        std::string_view artColor,
        const std::vector<std::string_view>& options,
        int selectedIndex,
        std::string_view selectedColor,
        std::string_view resetColor
    );

    void runGenericMenu(
        const std::vector<std::string_view>& titleLines,
        size_t titleArtWidth,
        const std::vector<std::string_view>& options,
        const std::vector<std::function<void()>>& actions,
        bool allowEscExit = true
    );
}

#endif // ELDERGLYPH_CONSOLEUI_H
