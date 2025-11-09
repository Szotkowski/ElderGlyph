#ifndef ELDERGLYPH_MENUCONSTANTS_H
#define ELDERGLYPH_MENUCONSTANTS_H

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

    constexpr std::size_t TITLE_LINE_COUNT = TITLE_LINES.size();

    constexpr std::size_t TITLE_ART_WIDTH = TITLE_LINES[0].length();

    constexpr std::array<std::string_view, 6> MENU_OPTIONS = {"New game", "Load game", "Settings", "Help", "Credits", "Quit"};

    constexpr std::size_t NUM_MENU_OPTIONS = MENU_OPTIONS.size();
}

#endif // ELDERGLYPH_MENUCONSTANTS_H
