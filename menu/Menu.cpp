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
    constexpr int numOptions = GameEngineConstants::NUM_OPTIONS;

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
                handleOptionSelection(static_cast<MenuTypes::OptionIndex>(currentIndex));
                shouldRedrawMenu = true;
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
    ConsoleUI::drawFrameContent(
        std::vector(
            GameEngineConstants::TITLE_LINES.begin(),
            GameEngineConstants::TITLE_LINES.end()
        ),
        GameEngineConstants::TITLE_ART_WIDTH,
        GREEN_NORMAL_TEXT,
        std::vector(
            GameEngineConstants::OPTIONS.begin(),
            GameEngineConstants::OPTIONS.end()
        ),
        currentIndex,
        GREEN_NORMAL_TEXT,
        RESET_TEXT
    );
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
        LOG_INFO("Loading games list.");
        GameEngine::loadGames();
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
