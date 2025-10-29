#include "Menu.h"

Menu::Menu()
{
    LOG_INFO("Creating Menu instance.");
}

Menu::~Menu()
{
    LOG_INFO("Destroying Menu instance.");
}

Menu& Menu::getInstance()
{
    static Menu instance;
    return instance;
}

void Menu::drawOption(const std::string& option, int width, MenuTypes::OptionIndex index, int currentIndex)
{
    bool isSelected = static_cast<int>(index) == currentIndex;

    constexpr int MARKER_CHARS = 2;

    std::cout << "#";

    int total_padding = width - option.length() - MenuConstants::PADDING_FACTOR;
    int padding_left = total_padding / 2;
    int padding_right = total_padding - padding_left;

    std::cout << std::setw(padding_left) << std::left << "";

    if (isSelected)
    {
        std::cout << GREEN_NORMAL_TEXT << option << " <" << std::setw(padding_right - MARKER_CHARS) << std::right << "";
    }
    else
    {
        std::cout << option << std::setw(padding_right) << std::right << "";
    }

    std::cout << RESET_TEXT << "  #" << "\n";
}

void Menu::drawHorizontalBorder(int width, bool isEndOfWindow)
{
    std::cout << std::string(width, '#');
    if (!isEndOfWindow)
    {
        std::cout << "\n";
    }
}

void Menu::drawEmptyFrameLine(int width, int count)
{
    for (int i = 0; i < count; ++i)
    {
        std::cout << "#" << std::setw(width - 2) << "" << "#" << "\n";
    }
}

void Menu::drawTitle(int consoleWidth)
{
    for (const std::string& line : MenuConstants::TITLE_LINES)
    {
        int padding_left = (consoleWidth - MenuConstants::TITLE_ART_WIDTH - 2) / 2;

        std::cout << "#";
        std::cout << std::setw(padding_left) << "";

        std::cout << GREEN_NORMAL_TEXT << line << RESET_TEXT;

        std::cout << std::setw(consoleWidth - MenuConstants::TITLE_ART_WIDTH - 1 - padding_left) << "";
        std::cout << "#" << "\n";
    }
}

void Menu::drawFullMenu(int consoleWidth, int consoleHeight, int currentIndex)
{
    const int numOptions = MenuConstants::NUM_OPTIONS;
    const int totalOptionsLines = numOptions + ((numOptions - 1) * MenuConstants::SEPARATOR_LINES);

    int occupied_lines = MenuConstants::BORDER_LINES + MenuConstants::TITLE_LINE_COUNT + totalOptionsLines +
        MenuConstants::LINE_PADDING_AFTER_TITLE;

    int total_empty_space = std::max(0, consoleHeight - occupied_lines);
    int numEmptyLines_top = total_empty_space / 2;
    int numEmptyLines_bottom = total_empty_space - numEmptyLines_top;

    drawHorizontalBorder(consoleWidth);

    drawEmptyFrameLine(consoleWidth, std::max(0, numEmptyLines_top));

    drawTitle(consoleWidth);

    drawEmptyFrameLine(consoleWidth, MenuConstants::LINE_PADDING_AFTER_TITLE);

    for (int i = 0; i < numOptions; ++i)
    {
        drawOption(MenuConstants::OPTIONS[i], consoleWidth, static_cast<MenuTypes::OptionIndex>(i), currentIndex);

        if (i < numOptions - 1)
        {
            drawEmptyFrameLine(consoleWidth, MenuConstants::SEPARATOR_LINES);
        }
    }

    drawEmptyFrameLine(consoleWidth, std::max(0, numEmptyLines_bottom));

    drawHorizontalBorder(consoleWidth, true);
}


void Menu::handleOptionSelection(MenuTypes::OptionIndex option)
{
    switch (option)
    {
    case MenuTypes::OptionIndex::NEW_GAME:
        LOG_INFO("Creating new game.");
        GameEngine::newGame();
        break;
    case MenuTypes::OptionIndex::LOAD_GAME:
        LOG_INFO("Loading game.");
        GameEngine::loadGame();
        break;
    case MenuTypes::OptionIndex::OPTIONS:
        LOG_INFO("Opening options.");
        GameEngine::options();
        break;
    case MenuTypes::OptionIndex::HELP:
        LOG_INFO("Showing help screen.");
        break;
    case MenuTypes::OptionIndex::QUIT:
        LOG_INFO("Stopping game...");
        GameEngine::quit();
        exit(0);
        break;
    default:
        LOG_WARNING("Invalid menu option selected.");
        break;
    }
}

void Menu::showMenu()
{
#ifndef _WIN32
    std::cout << "Menu functionality is currently Windows-dependent.\n";
    return;
#else
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;

    int currentIndex = 0;
    bool shouldRedrawMenu = true;

    do
    {
        if (_kbhit())
        {
            int key = _getch();

            if (key == static_cast<int>(MenuTypes::KeyCode::EXTENDED) || key == 224)
            {
                key = _getch();
            }

            const int numOptions = MenuConstants::NUM_OPTIONS;

            switch (key)
            {
            case 'w':
            case 'W':
            case static_cast<int>(MenuTypes::KeyCode::UP_ARROW):
                currentIndex = (currentIndex == 0) ? numOptions - 1 : currentIndex - 1;
                shouldRedrawMenu = true;
                break;
            case 's':
            case 'S':
            case static_cast<int>(MenuTypes::KeyCode::DOWN_ARROW):
                currentIndex = (currentIndex == numOptions - 1) ? 0 : currentIndex + 1;
                shouldRedrawMenu = true;
                break;
            case static_cast<int>(MenuTypes::KeyCode::ENTER):
                handleOptionSelection(static_cast<MenuTypes::OptionIndex>(currentIndex));
                shouldRedrawMenu = true;
                break;
            default:
                break;
            }
        }

        if (shouldRedrawMenu)
        {
            GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
            int consoleWidth = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
            int consoleHeight = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;

            drawFullMenu(consoleWidth, consoleHeight, currentIndex);
            shouldRedrawMenu = false;
        }

        FlushConsoleInputBuffer(hConsole);
    }
    while (true);
#endif
}
