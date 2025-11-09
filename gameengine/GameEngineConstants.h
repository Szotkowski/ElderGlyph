#ifndef ELDERGLYPH_GAMEENGINECONSTANTS_H
#define ELDERGLYPH_GAMEENGINECONSTANTS_H

#include <string_view>
#include <array>

namespace GameEngineConstants
{
    constexpr std::array<std::string_view, 7> DEATH_TITLE_LINES = {
        "##    ##  #######  ##     ##       ########  #### ######## ######## ",
        " ##  ##  ##     ## ##     ##       ##     ##  ##  ##       ##     ##",
        "  ####   ##     ## ##     ##       ##     ##  ##  ##       ##     ##",
        "   ##    ##     ## ##     ##       ##     ##  ##  ######   ##     ##",
        "   ##    ##     ## ##     ##       ##     ##  ##  ##       ##     ##",
        "   ##    ##     ## ##     ##       ##     ##  ##  ##       ##     ##",
        "   ##     #######   #######        ########  #### ######## ######## "
    };

    constexpr std::size_t DEATH_TITLE_LINE_COUNT = DEATH_TITLE_LINES.size();

    constexpr std::size_t DEATH_TITLE_ART_WIDTH = DEATH_TITLE_LINES[0].length();

    constexpr std::array<std::string_view, 1> CHARACTER_CLASS_TITLE_LINES = {"CHOOSE CLASS"};

    constexpr std::array<std::string_view, 4> CHARACTER_CLASS_OPTIONS = {"Warrior", "Mage", "Archer", "Back"};

    constexpr std::size_t NUM_CHARACTER_CLASS_OPTIONS = CHARACTER_CLASS_OPTIONS.size();

    constexpr std::array<std::string_view, 1> DIFFICULTY_TITLE_LINES = {"SET DIFFICULTY"};

    constexpr std::array<std::string_view, 4> DIFFICULTY_OPTIONS = {"Easy", "Normal", "Hard", "Back"};

    constexpr std::size_t NUM_DIFFICULTY_OPTIONS = DIFFICULTY_OPTIONS.size();

    constexpr std::array<std::string_view, 1> LOAD_GAME_TITLE_LINES = {"LOAD/DELETE GAME"};

    constexpr std::array<std::string_view, 3> LOAD_GAME_OPTIONS = {"Load", "Delete", "Back"};

    constexpr std::size_t NUM_LOAD_GAME_OPTIONS = LOAD_GAME_OPTIONS.size();

    constexpr std::array<std::string_view, 1> GAME_SETTINGS_TITLE_LINES = {"GAME SETTINGS"};

    constexpr std::array<std::string_view, 2> GAME_SETTINGS_OPTIONS = {"Log", "Back"};

    constexpr std::size_t NUM_GAME_SETTINGS_OPTIONS = GAME_SETTINGS_OPTIONS.size();

    constexpr std::array<std::string_view, 1> HELP_TITLE_LINES = {"HELP & INSTRUCTIONS"};

    constexpr std::array<std::string_view, 1> HELP_OPTIONS = {"Back"};

    constexpr std::size_t NUM_HELP_OPTIONS = HELP_OPTIONS.size();

    constexpr std::array<std::string_view, 1> CREDITS_TITLE_LINES = {"CREDITS"};

    constexpr std::array<std::string_view, 1> CREDITS_OPTIONS = {"Back"};

    constexpr std::size_t NUM_CREDITS_OPTIONS = CREDITS_OPTIONS.size();

    constexpr std::array<std::string_view, 1> QUIT_TITLE_LINES = {"Do you really want to quit?"};

    constexpr std::array<std::string_view, 2> QUIT_OPTIONS = {"Yes", "No"};

    constexpr std::size_t NUM_QUIT_OPTIONS = QUIT_OPTIONS.size();

    constexpr std::array<std::string_view, 1> DEATH_TEXT_TITLE_LINES = {"GAME OVER"};

    constexpr std::array<std::string_view, 1> DEATH_OPTIONS = {"Back to menu"};

    constexpr std::size_t NUM_DEATH_OPTIONS = DEATH_OPTIONS.size();
}

#endif // ELDERGLYPH_GAMEENGINECONSTANTS_H
