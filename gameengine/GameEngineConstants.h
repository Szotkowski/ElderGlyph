#ifndef ELDERGLYPH_GAMEENGINECONSTANTS_H
#define ELDERGLYPH_GAMEENGINECONSTANTS_H

#include <string_view>
#include <array>
#include <cstddef>

namespace GameEngineConstants
{
    inline constexpr std::array<std::string_view, 7> DEATH_TITLE_LINES = {
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
}

#endif // ELDERGLYPH_GAMEENGINECONSTANTS_H
