#include "GameEngine.h"

// Assuming these are defined and available:
// #include "Map.h"
// #include "Inventory.h"
// #include "Player.h"
// #include "ConsoleUI.h"
// #include "Menu.h"
// #include "AnsiCodes.h"
// #include "KeyCodes.h"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstdlib> // For exit()

#include "../console/ConsoleUI.h"
#include "GameEngineTypes.h"

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#endif

using namespace Input; // Using KeyCode enum

GameEngine::GameEngine()
{
    LOG_INFO("Creating GameEngine object.");
}

GameEngine::~GameEngine()
{
    LOG_INFO("Destroying GameEngine object.");
}

GameEngine& GameEngine::getInstance()
{
    static GameEngine instance;
    return instance;
}

void GameEngine::gameLoop()
{
    LOG_INFO("Game started.");
    //Map::getInstance().displayCurrentMap();
    while (true)
    {
        if (_kbhit())
        {
            // Standardize input to use int key codes
            int key = _getch();

            if (key == static_cast<int>(KeyCode::EXTENDED_KEY_1) || key == static_cast<int>(KeyCode::EXTENDED_KEY_2))
            {
                key = _getch(); // Read the extended key code
            }

            // Pass the raw key code to handlePlayerInput (which will cast to char for 'w', 'a', etc.)
            if (handlePlayerInput(static_cast<char>(key)))
            {
                //Map::getInstance().displayCurrentMap();
            }
        }
    }
}

bool GameEngine::handlePlayerInput(char input)
{
    bool shouldRedrawMap;
    //Player* player = Map::getInstance().getCurrentLocation()->getPlayer();
    /*if (player == nullptr)
    {
        std::cerr << RED_NORMAL_TEXT << "Player not found." << RESET_TEXT << "\n";
        LOG_ERROR("Player not found.");
        return false;
    }*/

    // Key code comparison is safer as int, but for char moves, char is fine
    switch (input)
    {
    case 'w':
    case 'W':
        //shouldRedrawMap = player->movePlayer('w');
        break;
    case 's':
    case 'S':
        //shouldRedrawMap = player->movePlayer('s');
        break;
    case 'a':
    case 'A':
        //shouldRedrawMap = player->movePlayer('a');
        break;
    case 'd':
    case 'D':
        //shouldRedrawMap = player->movePlayer('d');
        break;
    case 'e':
    case 'E':
        //Inventory::getInstance().printInventory();
        shouldRedrawMap = false;
        break;
    case static_cast<char>(KeyCode::ESC):
        saveGame();
        Menu::showMenu();
        shouldRedrawMap = false;
        break;
    default:
        // Handle arrow keys received as extended key codes
        switch (static_cast<KeyCode>(input))
        {
            case KeyCode::UP_ARROW:
                //shouldRedrawMap = player->movePlayer('w');
                break;
            case KeyCode::DOWN_ARROW:
                //shouldRedrawMap = player->movePlayer('s');
                break;
            case KeyCode::LEFT_ARROW:
                //shouldRedrawMap = player->movePlayer('a');
                break;
            case KeyCode::RIGHT_ARROW:
                //shouldRedrawMap = player->movePlayer('d');
                break;
            default:
                shouldRedrawMap = false;
                break;
        }
        break;
    }
    return shouldRedrawMap;
}

int GameEngine::runSubMenu(const std::string& title, const std::vector<std::string>& content)
{
    // *** CORE LOGIC RETAINED ***
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    int consoleWidth = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
    int consoleHeight = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top - 5; // Note: -3 adjustment retained
    int currentIndex = 0;

    bool shouldRedrawMenu = true;
    int numOptions = content.size();

    do
    {
        if (_kbhit())
        {
            int key = _getch();
            if (key == static_cast<int>(KeyCode::EXTENDED_KEY_1) || key == static_cast<int>(KeyCode::EXTENDED_KEY_2))
            {
                key = _getch();
            }

            switch (key)
            {
            case 'w':
            case static_cast<int>(KeyCode::UP_ARROW):
                currentIndex = (currentIndex == 0) ? numOptions - 1 : currentIndex - 1;
                shouldRedrawMenu = true;
                break;
            case 's':
            case static_cast<int>(KeyCode::DOWN_ARROW):
                currentIndex = (currentIndex == numOptions - 1) ? 0 : currentIndex + 1;
                shouldRedrawMenu = true;
                break;
            case static_cast<int>(KeyCode::ENTER):
                {
                    if (title == "Load Game:")
                    {
                        return currentIndex;
                    }
                    handleSubMenuSelection(title, currentIndex);
                    shouldRedrawMenu = true;
                }
                break;
            case static_cast<int>(KeyCode::ESC):
                Menu::showMenu();
                // Sub-menu will exit here, returning -1 to signal back to menu/game
                return -1;
            default:
                break;
            }
        }
        if (shouldRedrawMenu)
        {
            drawSubWindow(consoleWidth, consoleHeight, content, currentIndex, title);
            shouldRedrawMenu = false;
        }
        FlushConsoleInputBuffer(hConsole);
    }
    while (true);
}

void GameEngine::handleSubMenuSelection(const std::string& title, int currentIndex)
{
    // *** CORE LOGIC RETAINED ***
    if (title == "Options:")
    {
        if (currentIndex == static_cast<int>(GameEngineTypes::GameMenuOption::LOG))
        {
            Logger::showLog();
        }
        else
        {
            Menu::showMenu();
        }
    }
    else if (title == "Do you really want to quit?")
    {
        if (currentIndex == static_cast<int>(GameEngineTypes::QuitOption::YES))
        {
            LOG_INFO("Stopping game...");
            exit(0);
        }
        Menu::showMenu();
    }
}

void GameEngine::drawSubWindow(int consoleWidth, int consoleHeight, const std::vector<std::string>& content,
                               int currentIndex, const std::string& title)
{
    bool isLoadGame = (title == "Load Game:");

    int numEmptyLines = ((consoleHeight - content.size() - 1) / 2);

    if (isLoadGame)
    {
        numEmptyLines = 7;
    }

    // --- REPLACED drawHorizontalBorder with ConsoleUI call
    ConsoleUI::drawHorizontalBorder(consoleWidth);

    // --- REPLACED drawEmptyFrameLine with ConsoleUI call
    ConsoleUI::drawEmptyFrameLine(consoleWidth, numEmptyLines);

    // --- REPLACED custom title drawing with ConsoleUI call
    ConsoleUI::drawCenteredLine(consoleWidth, title, GREEN_NORMAL_TEXT);

    if (isLoadGame)
    {
        // --- REPLACED drawEmptyFrameLine with ConsoleUI call
        ConsoleUI::drawEmptyFrameLine(consoleWidth, 2);
    }
    else
    {
        // Note: The original logic here (numEmptyLines - 7) seems odd if numEmptyLines was just calculated above,
        // but we retain the calculation to preserve existing layout logic.
        // --- REPLACED drawEmptyFrameLine with ConsoleUI call
        ConsoleUI::drawEmptyFrameLine(consoleWidth, numEmptyLines - 6);
    }

    // Loop to draw options
    for (size_t i = 0; i < content.size(); ++i)
    {
        // --- REPLACED drawOption with ConsoleUI::drawCenteredOption call
        // IMPORTANT: The original implementation in GameEngine was confusingly structured (passing i != currentIndex).
        // We normalize the boolean to correctly reflect selection (i == currentIndex).
        ConsoleUI::drawCenteredOption(
            consoleWidth,
            content[i],
            i == currentIndex,
            GREEN_NORMAL_TEXT,
            RESET_TEXT,
            MenuConstants::PADDING_FACTOR
        );

        // --- REPLACED drawEmptyFrameLine with ConsoleUI call
        ConsoleUI::drawEmptyFrameLine(consoleWidth, 1);
    }

    if (isLoadGame)
    {
        // --- REPLACED drawEmptyFrameLine with ConsoleUI call
        ConsoleUI::drawEmptyFrameLine(consoleWidth, consoleHeight - (numEmptyLines + 3 + 1 + content.size() * 2) + 3);
    }
    else
    {
        // --- REPLACED drawEmptyFrameLine with ConsoleUI call
        ConsoleUI::drawEmptyFrameLine(consoleWidth, numEmptyLines-1);
    }

    // --- REPLACED drawHorizontalBorder with ConsoleUI call
    ConsoleUI::drawHorizontalBorder(consoleWidth, true);
}

std::vector<std::string> GameEngine::getSavedMaps(const std::string& saveDirectory)
{
    std::vector<std::string> savedMaps;
    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(saveDirectory))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".bin")
        {
            savedMaps.push_back(entry.path().stem().string());
        }
    }
    return savedMaps;
}

void GameEngine::loadSelectedMap(const std::string& saveDirectory, const std::string& selectedMap)
{
    std::string filePath = saveDirectory + "/" + selectedMap + ".bin";

    std::ifstream file(filePath, std::ios::binary);
    if (!file)
    {
        std::cerr << RED_NORMAL_TEXT << "Failed to open file for reading." << RESET_TEXT << "\n";
        LOG_ERROR("Failed to open file for reading.");
        Menu::showMenu();
        return;
    }

    //Map::loadMap(file);
    //Inventory::loadInventory(file);

    if (file.is_open())
    {
        file.close();
    }
}

// REMOVED: Implementation of GameEngine::drawOption
// REMOVED: Implementation of GameEngine::drawHorizontalBorder
// REMOVED: Implementation of GameEngine::drawEmptyFrameLine

void GameEngine::deathScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    int consoleWidth = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
    int consoleHeight = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
    constexpr int numOptions = 1;

    constexpr int TITLE_LINES = GameEngineConstants::DEATH_TITLE_LINE_COUNT;
    constexpr int FIXED_LINES = 4;
    int occupied_lines = TITLE_LINES + FIXED_LINES + numOptions + 2;
    int numEmptyLines = (consoleHeight - occupied_lines) / 2;

    // --- REPLACED drawHorizontalBorder with ConsoleUI call
    ConsoleUI::drawHorizontalBorder(consoleWidth);

    // --- REPLACED drawEmptyFrameLine with ConsoleUI call
    ConsoleUI::drawEmptyFrameLine(consoleWidth, numEmptyLines);

    // --- REPLACED drawDeathTitle with ConsoleUI::drawCenteredArt call
    ConsoleUI::drawCenteredArt(
        consoleWidth,
        GameEngineConstants::DEATH_TITLE_ART_WIDTH,
        GameEngineConstants::DEATH_TITLE_LINES,
        GREEN_NORMAL_TEXT,
        RESET_TEXT
    );

    // --- REPLACED drawEmptyFrameLine with ConsoleUI call
    ConsoleUI::drawEmptyFrameLine(consoleWidth, 2);

    // --- REPLACED drawOption with ConsoleUI::drawCenteredOption call
    // The option is "Back to menu" and it is always selected (currentIndex is implicitly 0)
    ConsoleUI::drawCenteredOption(
        consoleWidth,
        "Back to menu",
        true, // Always selected since it's the only option
        GREEN_NORMAL_TEXT,
        RESET_TEXT,
        MenuConstants::PADDING_FACTOR
    );

    // --- REPLACED drawEmptyFrameLine with ConsoleUI call
    ConsoleUI::drawEmptyFrameLine(consoleWidth, numEmptyLines + 2);

    // --- REPLACED drawHorizontalBorder with ConsoleUI call
    ConsoleUI::drawHorizontalBorder(consoleWidth, true);

    while (_getch() != static_cast<int>(KeyCode::ENTER))
    {
    }
    Menu::showMenu();
}

void GameEngine::newGame()
{
    //Map::getInstance().setMapName();
    //Map::getInstance().setMapDifficulty();
    //LOG_INFO("Created map with name: " + Map::getInstance().getMapName());
    //Map::getInstance().createNewLocation(true);
    // Inventory::getInstance(); // Instance is created on first use, but explicit call is fine.
    //saveGame();
    //gameLoop();
}

void GameEngine::saveGame()
{
    //LOG_INFO("Game " + Map::getInstance().getMapName() + " saving.");

    const std::string saveDirectory = "saves";
    std::filesystem::create_directory(saveDirectory);

    //std::string filePath = saveDirectory + "/" + Map::getInstance().getMapName() + ".bin";
    /*std::ofstream file(filePath, std::ios::binary);
    if (!file)
    {
        std::cerr << RED_NORMAL_TEXT << "Failed to open file for writing." << RESET_TEXT << "\n";
        LOG_ERROR("Failed to open file for writing.");
        Menu::showMenu();
        return;
    }

    Map::getInstance().saveMap(file);
    Inventory::getInstance().saveInventory(file);

    if (file.is_open())
    {
        file.close();
    }

    std::cout << "Game saved successfully." << "\n";
    LOG_INFO("Game " + Map::getInstance().getMapName() + " saved.");*/
}

void GameEngine::loadGame()
{
    std::cout << "Game loading." << "\n";

    const std::string saveDirectory = "saves";

    if (!std::filesystem::exists(saveDirectory))
    {
        if (!std::filesystem::create_directory(saveDirectory))
        {
            std::cerr << RED_NORMAL_TEXT << "Failed to create save directory." << RESET_TEXT << "\n";
            LOG_ERROR("Failed to create save directory.");
        }
        else
        {
            std::cout << YELLOW_NORMAL_TEXT << "Save directory created. No saved maps found." << RESET_TEXT << "\n";
            LOG_WARNING("Save directory created. No saved maps found.");
        }
    }

    std::vector<std::string> savedMaps = getSavedMaps(saveDirectory);
    const std::string loadGameTitle = "Load Game:";

    if (savedMaps.empty())
    {
        std::cout << YELLOW_NORMAL_TEXT << "No saved maps found." << RESET_TEXT << "\n";
        LOG_WARNING("No saved maps found.");
        Menu::showMenu();
        return;
    }

    int selectedMapIndex = runSubMenu(loadGameTitle, savedMaps);

    if (selectedMapIndex < 0 || selectedMapIndex >= savedMaps.size())
    {
        Menu::showMenu();
        return;
    }

    const std::string& selectedMap = savedMaps[selectedMapIndex];
    loadSelectedMap(saveDirectory, selectedMap);

    std::cout << "Game loaded successfully." << "\n";
    LOG_INFO("Game loaded successfully.");

    gameLoop();
}

void GameEngine::settings()
{
    std::vector<std::string> optionsContent = {"Open log", "Back"};
    const std::string optionsTitle = "Options:";

    runSubMenu(optionsTitle, optionsContent);
}

void GameEngine::help()
{
    std::vector<std::string> optionsContent = {"Open log", "Back"};
    const std::string optionsTitle = "Options:";

    runSubMenu(optionsTitle, optionsContent);
}

void GameEngine::credits()
{
    std::vector<std::string> optionsContent = {"Open log", "Back"};
    const std::string optionsTitle = "Options:";

    runSubMenu(optionsTitle, optionsContent);
}

void GameEngine::quit()
{
    std::vector<std::string> quitOptions = {"Yes", "No"};
    const std::string quitTitle = "Do you really want to quit?";

    runSubMenu(quitTitle, quitOptions);
}

// REMOVED: Implementation of GameEngine::drawDeathTitle
