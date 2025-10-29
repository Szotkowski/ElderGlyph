#ifndef ELDERGLYPH_GAMEENGINETYPES_H
#define ELDERGLYPH_GAMEENGINETYPES_H

namespace GameEngineTypes
{
    enum class InputKey
    {
        UP_ARROW = 72,
        DOWN_ARROW = 80,
        LEFT_ARROW = 75,
        RIGHT_ARROW = 77,
        ESC = 27,
        ENTER = 13,
        EXTENDED_KEY_1 = -32,
        EXTENDED_KEY_2 = 0
    };

    enum class GameMenuOption
    {
        LOG = 0,
        BACK
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
