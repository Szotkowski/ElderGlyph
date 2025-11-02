#ifndef ELDERGLYPH_GAMEENGINE_H
#define ELDERGLYPH_GAMEENGINE_H

#include "../menu/Menu.h"
#include "../logger/Logger.h"
#include "../KeyCodes.h"
#include "GameEngineConstants.h"

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#endif

class GameEngine
{
private:
    GameEngine();

    ~GameEngine();

    static void gameLoop();
    static bool handlePlayerInput(char input);

    static int runSubMenu(const std::string& title, const std::vector<std::string>& content);

    static void handleSubMenuSelection(const std::string& title, int currentIndex);

    static void drawSubWindow(int consoleWidth, int consoleHeight, const std::vector<std::string>& options,
                              int currentIndex, const std::string& title);

    static std::vector<std::string> getSavedMaps(const std::string& saveDirectory);

    static void loadSelectedMap(const std::string& saveDirectory, const std::string& selectedMap);

    static void drawOption(const std::string& option, int width, bool isSelected);

    static void drawHorizontalBorder(int width, bool isEndOfWindow = false);

    static void drawEmptyFrameLine(int width, int count);

    static void drawDeathTitle(int consoleWidth);

public:
    static GameEngine& getInstance();

    static void newGame();

    static void saveGame();

    static void loadGame();

    static void settings();

    static void help();

    static void credits();

    static void quit();

    static void deathScreen();

    GameEngine(const GameEngine&) = delete;

    GameEngine& operator=(const GameEngine&) = delete;

    GameEngine(GameEngine&&) = delete;

    GameEngine& operator=(GameEngine&&) = delete;
};

#endif // ELDERGLYPH_GAMEENGINE_H
