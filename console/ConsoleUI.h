#ifndef ELDERGLYPH_CONSOLEUI_H
#define ELDERGLYPH_CONSOLEUI_H

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <string_view>
#include <algorithm>
#include <cstddef>

namespace ConsoleUI
{
    void drawHorizontalBorder(int width, bool isEndOfWindow = false);

    void drawEmptyFrameLine(int width, int count);

    void drawCenteredLine(int width, std::string_view content, std::string_view colorCode = "");

    void drawCenteredOption(int width, std::string_view option, bool isSelected,
                            std::string_view selectedColor, std::string_view resetColor, int paddingFactor);

    template <typename TContainer>
        void drawCenteredArt(const int consoleWidth, const std::size_t artWidth,
                             const TContainer& artLines,
                             const std::string_view artColor, std::string_view resetColor)
    {
        int padding = ((consoleWidth - artWidth) / 2) - 1;
        if (padding < 0) padding = 0;

        for (const auto& line : artLines)
        {
            std::cout << "#" << artColor << std::string(padding, ' ') << line << resetColor << std::string(padding, ' ') << "#" << "\n";
        }
    }
}

#endif // ELDERGLYPH_CONSOLEUI_H
