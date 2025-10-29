#ifndef ELDERGLYPH_MENUCONSTANTS_H
#define ELDERGLYPH_MENUCONSTANTS_H

#include <string>
#include <array>

namespace MenuConstants
{
    constexpr int TITLE_ART_WIDTH = 100;
    constexpr int PADDING_FACTOR = 4;

    constexpr int TITLE_LINE_COUNT = 7;
    constexpr int BORDER_LINES = 2;
    constexpr int SEPARATOR_LINES = 1;
    constexpr int LINE_PADDING_AFTER_TITLE = 2;
    constexpr int MIN_EMPTY_LINES = 2;

    const std::array<std::string, TITLE_LINE_COUNT> TITLE_LINES = {
        "######## ##       ########  ######## ########        ######   ##       ##    ## ########  ##     ##",
        "##       ##       ##     ## ##       ##     ##      ##    ##  ##        ##  ##  ##     ## ##     ##",
        "##       ##       ##     ## ##       ##     ##      ##        ##         ####   ##     ## ##     ##",
        "######   ##       ##     ## ######   ########       ##   #### ##          ##    ########  #########",
        "##       ##       ##     ## ##       ##   ##        ##    ##  ##          ##    ##        ##     ##",
        "##       ##       ##     ## ##       ##    ##       ##    ##  ##          ##    ##        ##     ##",
        "######## ######## ########  ######## ##     ##       ######   ########    ##    ##        ##     ##"
    };

    const std::array<std::string, 5> OPTIONS = {"New game", "Load game", "Options", "Help", "Quit"};
    constexpr int NUM_OPTIONS = OPTIONS.size();
}

#endif // ELDERGLYPH_MENUCONSTANTS_H
