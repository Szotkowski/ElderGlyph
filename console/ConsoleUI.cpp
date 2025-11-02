#include "../console/ConsoleUI.h"
#include "../AnsiCodes.h"

namespace ConsoleUI
{
    void drawHorizontalBorder(const int width, const bool isEndOfWindow)
    {
        std::cout << std::string(width, '#');
        if (!isEndOfWindow)
        {
            std::cout << "\n";
        }
    }

    void drawEmptyFrameLine(const int width, const int count)
    {
        for (int i = 0; i < count; ++i)
        {
            std::cout << "#" << std::setw(width - 2) << "" << "#" << "\n";
        }
    }

    void drawCenteredLine(const int width, const std::string_view content, const std::string_view colorCode)
    {
        const int content_length = static_cast<int>(content.length());
        const int padding_total = width - content_length - 2;

        const int padding_left = padding_total / 2;
        const int padding_right = padding_total - padding_left;

        std::cout << "#";
        std::cout << std::setw(padding_left) << "";

        std::cout << colorCode << content << RESET_TEXT;

        std::cout << std::setw(padding_right) << "";
        std::cout << "#" << "\n";
    }

    void drawCenteredOption(const int width, const std::string_view option, const bool isSelected,
                            const std::string_view selectedColor, const std::string_view resetColor, const int paddingFactor)
    {
        std::cout << "#";

        const int total_padding = width - static_cast<int>(option.length()) - paddingFactor;
        const int padding_left = total_padding / 2;
        const int padding_right = total_padding - padding_left;

        std::cout << std::setw(padding_left) << std::left << "";

        if (isSelected)
        {
            constexpr int MARKER_CHARS = 2;
            std::cout << selectedColor << option << " <" << std::setw(padding_right - MARKER_CHARS) << std::right << "";
        }
        else
        {
            std::cout << option << std::setw(padding_right) << std::right << "";
        }

        std::cout << resetColor << "  #" << "\n";
    }
}
