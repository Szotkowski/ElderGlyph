#ifndef ELDERGLYPH_MENUCONSTANTS_H
#define ELDERGLYPH_MENUCONSTANTS_H

#include <iostream>

namespace MenuConstants
{
    constexpr std::array<std::string_view, 7> TITLE_LINES = {
        "######## ##       ########  ######## ########         ######   ##       ##    ## ########  ##     ##",
        "##       ##       ##     ## ##       ##     ##       ##    ##  ##        ##  ##  ##     ## ##     ##",
        "##       ##       ##     ## ##       ##     ##       ##        ##         ####   ##     ## ##     ##",
        "######   ##       ##     ## ######   ########        ##   #### ##          ##    ########  #########",
        "##       ##       ##     ## ##       ##   ##         ##    ##  ##          ##    ##        ##     ##",
        "##       ##       ##     ## ##       ##    ##        ##    ##  ##          ##    ##        ##     ##",
        "######## ######## ########  ######## ##     ##        ######   ########    ##    ##        ##     ##"
    };

    constexpr std::array<std::string_view, 6> OPTIONS = {"New game", "Load game", "Settings", "Help", "Credits", "Quit"};

    constexpr std::size_t NUM_OPTIONS = OPTIONS.size();

    constexpr std::size_t TITLE_LINE_COUNT = TITLE_LINES.size();

    constexpr std::size_t TITLE_ART_WIDTH = TITLE_LINES[0].length();
}

#endif // ELDERGLYPH_MENUCONSTANTS_H
