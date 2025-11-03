#ifndef ELDERGLYPH_GAMEENGINETYPES_H
#define ELDERGLYPH_GAMEENGINETYPES_H

namespace GameEngineTypes
{
    enum class CharacterClassOption
    {
        WARRIOR = 0,
        MAGE,
        ARCHER,
        BACK
    };

    enum class DifficultyOption
    {
        EASY = 0,
        NORMAL,
        HARD,
        BACK
    };

    enum class LoadGameOption
    {
        LOAD = 0,
        DELETE_MAP,
        BACK
    };

    enum class GameSettingsOption
    {
        LOG = 0,
        BACK
    };

    enum class HelpOption
    {
        BACK = 0
    };

    enum class CreditsOption
    {
        BACK = 0
    };

    enum class QuitOption
    {
        YES = 0,
        NO
    };

    enum class DeathOption
    {
        BACK_TO_MENU = 0
    };
}

#endif // ELDERGLYPH_GAMEENGINETYPES_H
