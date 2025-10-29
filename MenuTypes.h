#ifndef ELDERGLYPH_MENUTYPES_H
#define ELDERGLYPH_MENUTYPES_H

namespace MenuTypes
{
    enum class KeyCode
    {
        ENTER = 13,
        UP_ARROW = 72,
        DOWN_ARROW = 80,
        EXTENDED = 0
    };

    enum class OptionIndex
    {
        NEW_GAME = 0,
        LOAD_GAME,
        OPTIONS,
        HELP,
        QUIT,
    };
}

#endif // ELDERGLYPH_MENUTYPES_H
