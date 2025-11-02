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

void Menu::showMenu()
{
#ifndef _WIN32
    std::cout << "Menu functionality is currently Windows-dependent.\n";
    return;
#else
    const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int currentIndex = 0;
    bool shouldRedrawMenu = true;

    do
    {
        if (_kbhit())
        {
            int key = _getch();

            if (key == static_cast<int>(Input::KeyCode::EXTENDED_KEY_1) || key == static_cast<int>(
                Input::KeyCode::EXTENDED_KEY_2))
            {
                key = _getch();
            }

            constexpr int numOptions = MenuConstants::NUM_OPTIONS;

            switch (key)
            {
            case 'w':
            case 'W':
            case static_cast<int>(Input::KeyCode::UP_ARROW):
                currentIndex = (currentIndex == 0) ? numOptions - 1 : currentIndex - 1;
                shouldRedrawMenu = true;
                break;
            case 's':
            case 'S':
            case static_cast<int>(Input::KeyCode::DOWN_ARROW):
                currentIndex = (currentIndex == numOptions - 1) ? 0 : currentIndex + 1;
                shouldRedrawMenu = true;
                break;
            case static_cast<int>(Input::KeyCode::ENTER):
                handleOptionSelection(static_cast<MenuTypes::OptionIndex>(currentIndex));
                shouldRedrawMenu = true;
                break;
            default:
                break;
            }
        }

        if (shouldRedrawMenu)
        {
            drawFullMenu(currentIndex);
            shouldRedrawMenu = false;
        }

        FlushConsoleInputBuffer(hConsole);
    }
    while (true);
#endif
}

void Menu::drawFullMenu(const int currentIndex)
{
    constexpr int consoleWidth = Console::WIDTH;
    constexpr int consoleHeight = Console::HEIGHT;
    constexpr int numOptions = MenuConstants::NUM_OPTIONS;
    constexpr int totalOptionsLines = numOptions + ((numOptions - 1) * MenuConstants::SEPARATOR_LINES);
    constexpr int occupied_lines = MenuConstants::BORDER_LINES + MenuConstants::TITLE_LINE_COUNT + totalOptionsLines +
        MenuConstants::LINE_PADDING_AFTER_TITLE;
    constexpr int total_empty_space = std::max(0, consoleHeight - occupied_lines);
    constexpr int numEmptyLines_top = total_empty_space / 2;
    constexpr int numEmptyLines_bottom = total_empty_space - numEmptyLines_top;

    ConsoleUI::drawHorizontalBorder(consoleWidth);
    ConsoleUI::drawEmptyFrameLine(consoleWidth, std::max(0, numEmptyLines_top));
    ConsoleUI::drawCenteredArt(
        consoleWidth,
        MenuConstants::TITLE_ART_WIDTH,
        MenuConstants::TITLE_LINES,
        GREEN_NORMAL_TEXT,
        RESET_TEXT
    );
    ConsoleUI::drawEmptyFrameLine(consoleWidth, MenuConstants::LINE_PADDING_AFTER_TITLE);

    for (int i = 0; i < numOptions; ++i)
    {
        const bool isSelected = i == currentIndex;

        ConsoleUI::drawCenteredOption(
            consoleWidth,
            MenuConstants::OPTIONS[i],
            isSelected,
            GREEN_NORMAL_TEXT,
            RESET_TEXT,
            MenuConstants::PADDING_FACTOR
        );

        if (i < numOptions - 1)
        {
            ConsoleUI::drawEmptyFrameLine(consoleWidth, MenuConstants::SEPARATOR_LINES);
        }
    }

    ConsoleUI::drawEmptyFrameLine(consoleWidth, std::max(0, numEmptyLines_bottom));
    ConsoleUI::drawHorizontalBorder(consoleWidth, true);
}

void Menu::handleOptionSelection(const MenuTypes::OptionIndex option)
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
    case MenuTypes::OptionIndex::SETTINGS:
        LOG_INFO("Opening settings.");
        GameEngine::settings();
        break;
    case MenuTypes::OptionIndex::HELP:
        LOG_INFO("Showing help screen.");
        GameEngine::help();
        break;
    case MenuTypes::OptionIndex::CREDITS:
        LOG_INFO("Showing credits screen.");
        GameEngine::credits();
        break;
    case MenuTypes::OptionIndex::QUIT:
        LOG_INFO("Stopping game...");
        GameEngine::quit();
        exit(0);
    default:
        LOG_WARNING("Invalid menu option selected.");
        break;
    }
}
