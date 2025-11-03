#include "GameEngine.h"

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
            int key = _getch();

            if (key == static_cast<int>(Input::KeyCode::EXTENDED_KEY_1) || key == static_cast<int>(
                Input::KeyCode::EXTENDED_KEY_2))
            {
                key = _getch();
            }

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
    case static_cast<char>(Input::KeyCode::ESC):
        saveGame();
        Menu::showMenu();
        shouldRedrawMap = false;
        break;
    default:
        switch (static_cast<Input::KeyCode>(input))
        {
        case Input::KeyCode::UP_ARROW:
            //shouldRedrawMap = player->movePlayer('w');
            break;
        case Input::KeyCode::DOWN_ARROW:
            //shouldRedrawMap = player->movePlayer('s');
            break;
        case Input::KeyCode::LEFT_ARROW:
            //shouldRedrawMap = player->movePlayer('a');
            break;
        case Input::KeyCode::RIGHT_ARROW:
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
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    int consoleWidth = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
    int consoleHeight = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top - 5;
    int currentIndex = 0;

    bool shouldRedrawMenu = true;
    int numOptions = content.size();

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

            switch (key)
            {
            case 'w':
            case static_cast<int>(Input::KeyCode::UP_ARROW):
                currentIndex = (currentIndex == 0) ? numOptions - 1 : currentIndex - 1;
                shouldRedrawMenu = true;
                break;
            case 's':
            case static_cast<int>(Input::KeyCode::DOWN_ARROW):
                currentIndex = (currentIndex == numOptions - 1) ? 0 : currentIndex + 1;
                shouldRedrawMenu = true;
                break;
            case static_cast<int>(Input::KeyCode::ENTER):
                {
                    if (title == "Load Game:")
                    {
                        return currentIndex;
                    }
                    handleSubMenuSelection(title, currentIndex);
                    shouldRedrawMenu = true;
                }
                break;
            case static_cast<int>(Input::KeyCode::ESC):
                Menu::showMenu();
                return -1;
            default:
                break;
            }
        }
        if (shouldRedrawMenu)
        {
            shouldRedrawMenu = false;
        }
        FlushConsoleInputBuffer(hConsole);
    }
    while (true);
}

void GameEngine::handleSubMenuSelection(const std::string& title, int currentIndex)
{
    if (title == "Options:")
    {
        if (currentIndex == static_cast<int>(GameEngineTypes::GameSettingsOption::LOG))
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

void GameEngine::newGame()
{
    //Map::getInstance().setMapName();
    //Map::getInstance().setMapDifficulty();
    //LOG_INFO("Created map with name: " + Map::getInstance().getMapName());
    //Map::getInstance().createNewLocation(true);
    //saveGame();
    //gameLoop();
}

void GameEngine::loadGames()
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
}

void GameEngine::deleteGame()
{
}

void GameEngine::settings()
{
}

void GameEngine::help()
{
}

void GameEngine::credits()
{
}

void GameEngine::quit()
{
}

void GameEngine::deathScreen(const int currentIndex)
{
    ConsoleUI::drawFrameContent(
        std::vector(
            GameEngineConstants::DEATH_TITLE_LINES.begin(),
            GameEngineConstants::DEATH_TITLE_LINES.end()
        ),
        GameEngineConstants::DEATH_TITLE_ART_WIDTH,
        GREEN_NORMAL_TEXT,
        std::vector(
            GameEngineConstants::DEATH_OPTIONS.begin(),
            GameEngineConstants::DEATH_OPTIONS.end()
        ),
        currentIndex,
        GREEN_NORMAL_TEXT,
        RESET_TEXT
    );

    while (_getch() != static_cast<int>(Input::KeyCode::ENTER))
    {
    }
    Menu::showMenu();
}
