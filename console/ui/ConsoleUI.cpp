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
        const int totalPaddingSpace = static_cast<int>(consoleWidth) - static_cast<int>(artWidth) - 2;
        if (totalPaddingSpace < 0)
        {
            for (const auto& line : artLines)
            {
                std::cout << "#" << artColor << line << resetColor << "#" << "\n";
            }
            return;
        }

        const int leftPadding = totalPaddingSpace / 2;
        const int rightPadding = totalPaddingSpace / 2 + (totalPaddingSpace % 2);

        for (const auto& line : artLines)
        {
            std::cout << "#" << artColor << std::string(leftPadding, ' ');
            std::cout << line << resetColor;
            std::cout << std::string(rightPadding, ' ') << "#" << "\n";
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

    void runGenericMenu(
        const std::vector<std::string_view>& titleLines,
        const std::size_t titleArtWidth,
        const std::vector<std::string_view>& options,
        const std::vector<std::function<void()>>& actions,
        const bool allowEscExit
    )
    {
        if (options.empty() || options.size() != actions.size()) {
            std::cerr << "Error: Invalid menu options or action list provided.\n";
            return;
        }

#ifndef _WIN32
        std::cout << "Menu functionality is currently Windows-dependent.\n";
        return;
#else
        const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        int currentIndex = 0;
        bool shouldRedrawMenu = true;
        bool menuActive = true;
        const int numOptions = static_cast<int>(options.size());

        do
        {
            if (_kbhit())
            {
                int key = _getch();

                if (key == static_cast<int>(Input::KeyCode::EXTENDED_KEY_1) ||
                    key == static_cast<int>(Input::KeyCode::EXTENDED_KEY_2))
                {
                    key = _getch();
                }

                if (key == 'w' || key == 'W' || key == static_cast<int>(Input::KeyCode::UP_ARROW))
                {
                    currentIndex = (currentIndex == 0) ? numOptions - 1 : currentIndex - 1;
                    shouldRedrawMenu = true;
                }
                else if (key == 's' || key == 'S' || key == static_cast<int>(Input::KeyCode::DOWN_ARROW))
                {
                    currentIndex = (currentIndex == numOptions - 1) ? 0 : currentIndex + 1;
                    shouldRedrawMenu = true;
                }
                else if (key == static_cast<int>(Input::KeyCode::ENTER))
                {
                    actions[currentIndex]();

                    if (options[currentIndex] == "Back" || options[currentIndex] == "Back to menu" ||
                        options[currentIndex] == "No")
                    {
                        menuActive = false;
                    }
                    else
                    {
                        shouldRedrawMenu = true;
                    }
                }
                else if (key == static_cast<int>(Input::KeyCode::ESC) && allowEscExit)
                {
                    menuActive = false;
                }
            }

            if (shouldRedrawMenu)
            {
                drawFrameContent(
                    titleLines,
                    titleArtWidth,
                    GREEN_NORMAL_TEXT,
                    options,
                    currentIndex,
                    GREEN_NORMAL_TEXT,
                    RESET_TEXT
                );
                shouldRedrawMenu = false;
            }

            FlushConsoleInputBuffer(hConsole);
        }
        while (menuActive);
#endif
    }
}
