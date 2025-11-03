#include "ConsoleUI.h"

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

    void drawCenteredOption(const int width, const std::string_view option, const bool isSelected,
                            const std::string_view selectedColor, const std::string_view resetColor)
    {
        constexpr int paddingFactor = ConsoleUIConstants::PADDING_FACTOR;

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

    void drawCenteredArt(const int consoleWidth, const std::size_t artWidth,
                         const std::vector<std::string_view>& artLines,
                         const std::string_view artColor, const std::string_view resetColor)
    {
        int padding = (static_cast<int>(consoleWidth) - static_cast<int>(artWidth)) / 2 - 1;
        if (padding < 0) padding = 0;

        for (const auto& line : artLines)
        {
            std::cout << "#" << artColor << std::string(padding, ' ') << line << resetColor << std::string(padding, ' ') << "#" << "\n";
        }
    }

    void drawFrameContent(
        const std::vector<std::string_view>& artLines,
        const std::size_t artWidth,
        const std::string_view artColor,
        const std::vector<std::string_view>& options,
        const int selectedIndex,
        const std::string_view selectedColor,
        const std::string_view resetColor
    )
    {
        constexpr int consoleWidth = Console::WIDTH;
        constexpr int consoleHeight = Console::HEIGHT;

        constexpr std::size_t borderLines = ConsoleUIConstants::BORDER_LINES;
        constexpr std::size_t separatorLines = ConsoleUIConstants::SEPARATOR_LINES;
        constexpr std::size_t paddingAfterTitle = ConsoleUIConstants::LINE_PADDING_AFTER_TITLE;

        const std::size_t numOptions = options.size();
        const std::size_t artLineCount = artLines.size();

        const std::size_t totalOptionsLines = numOptions + ((numOptions > 0) ? (numOptions - 1) * separatorLines : 0);
        const std::size_t occupied_lines = borderLines + artLineCount + paddingAfterTitle + totalOptionsLines;

        const int total_empty_space = std::max(0, static_cast<int>(consoleHeight) - static_cast<int>(occupied_lines));

        const int numEmptyLines_top = total_empty_space / 2;
        const int numEmptyLines_bottom = total_empty_space - numEmptyLines_top;

        drawHorizontalBorder(consoleWidth);
        drawEmptyFrameLine(consoleWidth, numEmptyLines_top);

        drawCenteredArt(
            consoleWidth,
            artWidth,
            artLines,
            artColor,
            resetColor
        );

        drawEmptyFrameLine(consoleWidth, paddingAfterTitle);

        for (std::size_t i = 0; i < numOptions; ++i)
        {
            const bool isSelected = static_cast<int>(i) == selectedIndex;

            drawCenteredOption(
                consoleWidth,
                options[i],
                isSelected,
                selectedColor,
                resetColor
            );

            if (i < numOptions - 1)
            {
                drawEmptyFrameLine(consoleWidth, separatorLines);
            }
        }

        drawEmptyFrameLine(consoleWidth, numEmptyLines_bottom);
        drawHorizontalBorder(consoleWidth, true);
    }
}
