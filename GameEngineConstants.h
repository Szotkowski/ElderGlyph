#ifndef ELDERGLYPH_GAMEENGINECONSTANTS_H
#define ELDERGLYPH_GAMEENGINECONSTANTS_H

#include <string>
#include <array>

namespace GameEngineConstants
{
    constexpr int DEATH_TITLE_LINE_COUNT = 7;
    constexpr int DEATH_TITLE_ART_WIDTH = 70;
    constexpr int DEATH_TITLE_LEFT_PADDING = 25;

    const std::array<std::string, DEATH_TITLE_LINE_COUNT> DEATH_TITLE_LINES = {
        "##    ##  #######  ##     ##       ########  #### ######## ######## ",
        " ##  ##  ##     ## ##     ##       ##     ##  ##  ##       ##     ##",
        "  ####   ##     ## ##     ##       ##     ##  ##  ##       ##     ##",
        "   ##    ##     ## ##     ##       ##     ##  ##  ######   ##     ##",
        "   ##    ##     ## ##     ##       ##     ##  ##  ##       ##     ##",
        "   ##    ##     ## ##     ##       ##     ##  ##  ##       ##     ##",
        "   ##     #######   #######        ########  #### ######## ######## "
    };
}

#endif // ELDERGLYPH_GAMEENGINECONSTANTS_H
