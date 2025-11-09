#include "Menu.h"

static const std::vector<std::function<void()>> s_main_menu_actions = {
    [] { LOG_INFO("Creating new game."); GameEngine::newGame(); },
    [] { LOG_INFO("Loading games list."); GameEngine::loadGames(); },
    [] { LOG_INFO("Opening settings."); GameEngine::settings(); },
    [] { LOG_INFO("Showing help screen."); GameEngine::help(); },
    [] { LOG_INFO("Showing credits screen."); GameEngine::credits(); },
    [] { LOG_INFO("Stopping game..."); GameEngine::quit(); }
};

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
    ConsoleUI::runGenericMenu(
        std::vector(MenuConstants::TITLE_LINES.begin(), MenuConstants::TITLE_LINES.end()),
        MenuConstants::TITLE_ART_WIDTH,
        std::vector(MenuConstants::MENU_OPTIONS.begin(), MenuConstants::MENU_OPTIONS.end()),
        s_main_menu_actions,
        false
    );
}
