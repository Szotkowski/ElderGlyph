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
    Map::getInstance().displayCurrentMap();
    while (true)
    {
        if (_kbhit())
        {
            char input = static_cast<char>(_getch());
            if (input == static_cast<char>(GameEngineTypes::InputKey::EXTENDED_KEY_1) || input == static_cast<char>(
                GameEngineTypes::InputKey::EXTENDED_KEY_2))
            {
                input = static_cast<char>(_getch());
            }
            if (handlePlayerInput(input))
            {
                Map::getInstance().displayCurrentMap();
            }
        }
    }
}

bool GameEngine::handlePlayerInput(char input)
{
    bool shouldRedrawMap;
    Player* player = Map::getInstance().getCurrentLocation()->getPlayer();
    if (player == nullptr)
    {
        std::cerr << RED_NORMAL_TEXT << "Player not found." << RESET_TEXT << "\n";
        LOG_ERROR("Player not found.");
        return false;
    }
    switch (input)
    {
    case 'w':
    case 'W':
    case static_cast<char>(GameEngineTypes::InputKey::UP_ARROW):
        shouldRedrawMap = player->movePlayer('w');
        break;
    case 's':
    case 'S':
    case static_cast<char>(GameEngineTypes::InputKey::DOWN_ARROW):
        shouldRedrawMap = player->movePlayer('s');
        break;
    case 'a':
    case 'A':
    case static_cast<char>(GameEngineTypes::InputKey::LEFT_ARROW):
        shouldRedrawMap = player->movePlayer('a');
        break;
    case 'd':
    case 'D':
    case static_cast<char>(GameEngineTypes::InputKey::RIGHT_ARROW):
        shouldRedrawMap = player->movePlayer('d');
        break;
    case 'e':
    case 'E':
        Inventory::getInstance().printInventory();
        shouldRedrawMap = false;
        break;
    case static_cast<char>(GameEngineTypes::InputKey::ESC):
        saveGame();
        Menu::showMenu();
        shouldRedrawMap = false;
        break;
    default:
        shouldRedrawMap = false;
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
    int consoleHeight = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top - 3;
    int currentIndex = 0;

    bool shouldRedrawMenu = true;
    int numOptions = content.size();

    do
    {
        if (_kbhit())
        {
            int key = _getch();
            if (key == static_cast<int>(GameEngineTypes::InputKey::EXTENDED_KEY_1) || key == static_cast<int>(
                GameEngineTypes::InputKey::EXTENDED_KEY_2))
            {
                key = _getch();
            }

            switch (key)
            {
            case 'w':
            case static_cast<int>(GameEngineTypes::InputKey::UP_ARROW):
                currentIndex = (currentIndex == 0) ? numOptions - 1 : currentIndex - 1;
                shouldRedrawMenu = true;
                break;
            case 's':
            case static_cast<int>(GameEngineTypes::InputKey::DOWN_ARROW):
                currentIndex = (currentIndex == numOptions - 1) ? 0 : currentIndex + 1;
                shouldRedrawMenu = true;
                break;
            case static_cast<int>(GameEngineTypes::InputKey::ENTER):
                {
                    if (title == "Load Game:")
                    {
                        return currentIndex;
                    }
                    handleSubMenuSelection(title, currentIndex);
                    shouldRedrawMenu = true;
                }
                break;
            case static_cast<int>(GameEngineTypes::InputKey::ESC):
                Menu::showMenu();
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

    int numEmptyLines = (consoleHeight - content.size() - 4) / 2;

    if (isLoadGame)
    {
        numEmptyLines = 7;
    }

    drawHorizontalBorder(consoleWidth);
    drawEmptyFrameLine(consoleWidth, numEmptyLines);

    int padding_left = (consoleWidth - title.length() - 2) / 2;
    int padding_right = consoleWidth - title.length() - 2 - padding_left;
    std::cout << "#" << std::setw(padding_left) << "" << title << std::setw(padding_right + 1) << "#" << "\n";

    if (isLoadGame)
    {
        drawEmptyFrameLine(consoleWidth, 2);
    }
    else
    {
        drawEmptyFrameLine(consoleWidth, numEmptyLines - 7);
    }

    for (size_t i = 0; i < content.size(); ++i)
    {
        drawOption(content[i], consoleWidth, i != currentIndex);
        drawEmptyFrameLine(consoleWidth, 1);
    }

    if (isLoadGame)
    {
        drawEmptyFrameLine(consoleWidth, consoleHeight - (numEmptyLines + 3 + 1 + content.size() * 2) + 3);
    }
    else
    {
        drawEmptyFrameLine(consoleWidth, numEmptyLines);
    }
    drawHorizontalBorder(consoleWidth, true);
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

    Map::loadMap(file);
    Inventory::loadInventory(file);

    if (file.is_open())
    {
        file.close();
    }
}

void GameEngine::drawOption(const std::string& option, int width, bool isSelected)
{
    constexpr int PADDING_FACTOR = 4;
    std::cout << "#";
    int padding_left = (width - option.length() - PADDING_FACTOR) / 2;
    int padding_right = width - option.length() - PADDING_FACTOR - padding_left;

    if (!isSelected)
    {
        std::cout << GREEN_NORMAL_TEXT;
        std::cout << std::setw(padding_left) << std::left << "" << option << " <" << std::setw(padding_right - 2) <<
            std::right << "";
    }
    else
    {
        std::cout << std::setw(padding_left) << std::left << "" << option << std::setw(padding_right) << std::right <<
            "";
    }

    std::cout << RESET_TEXT << "  #" << "\n";
}

void GameEngine::drawHorizontalBorder(int width, bool isEndOfWindow)
{
    std::cout << std::string(width, '#');
    if (!isEndOfWindow)
    {
        std::cout << "\n";
    }
}

void GameEngine::drawEmptyFrameLine(int width, int count)
{
    for (int i = 0; i < count; ++i)
    {
        std::cout << "#" << std::setw(width - 2) << "" << "#" << "\n";
    }
}

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

    drawHorizontalBorder(consoleWidth);
    drawEmptyFrameLine(consoleWidth, numEmptyLines);

    drawDeathTitle(consoleWidth + 2);

    drawEmptyFrameLine(consoleWidth, 2);

    drawOption("Back to menu", consoleWidth, static_cast<int>(GameEngineTypes::DeathOption::BACK_TO_MENU) != 0);

    drawEmptyFrameLine(consoleWidth, numEmptyLines + 2);

    drawHorizontalBorder(consoleWidth, true);

    while (_getch() != static_cast<int>(GameEngineTypes::InputKey::ENTER))
    {
    }
    Menu::showMenu();
}

void GameEngine::newGame()
{
    Map::getInstance().setMapName();
    Map::getInstance().setMapDifficulty();
    LOG_INFO("Created map with name: " + Map::getInstance().getMapName());
    Map::getInstance().createNewLocation(true);
    // Inventory::getInstance(); // Instance is created on first use, but explicit call is fine.
    saveGame();
    gameLoop();
}

void GameEngine::saveGame()
{
    LOG_INFO("Game " + Map::getInstance().getMapName() + " saving.");
    std::cout << "Game is saving." << "\n";

    const std::string saveDirectory = "saves";
    std::filesystem::create_directory(saveDirectory);

    std::string filePath = saveDirectory + "/" + Map::getInstance().getMapName() + ".bin";
    std::ofstream file(filePath, std::ios::binary);
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
    LOG_INFO("Game " + Map::getInstance().getMapName() + " saved.");
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

void GameEngine::options()
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

void GameEngine::drawDeathTitle(int consoleWidth)
{
    for (const std::string& line : GameEngineConstants::DEATH_TITLE_LINES)
    {
        constexpr int TITLE_ART_WIDTH = GameEngineConstants::DEATH_TITLE_ART_WIDTH;
        constexpr int LEFT_PADDING = GameEngineConstants::DEATH_TITLE_LEFT_PADDING;

        int right_padding = consoleWidth - TITLE_ART_WIDTH - LEFT_PADDING - 2;

        std::cout << "#" << std::setw(LEFT_PADDING) << "";
        std::cout << GREEN_NORMAL_TEXT << line << RESET_TEXT;
        std::cout << std::setw(right_padding + 1) << "#" << "\n";
    }
}
