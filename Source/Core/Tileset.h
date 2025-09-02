#pragma once

#include <raylib.h>

#include <string_view>
#include <vector>

#include <stdint.h>

namespace Squareball
{
    enum TileFlagsEnum : uint32_t
    {
        TileFlags_None      = 0,
        TileFlags_Wall      = 1 << 0,
        TileFlags_LeftGoal  = 1 << 1,
        TileFlags_RightGoal = 1 << 2,
    };
    
    using TileFlags = uint32_t;
    
    struct Tile
    {
        Vector2 TexCoords;
        TileFlags Flags;
    };
    
    struct Tileset
    {
        std::vector<Tile> Tiles;
        Texture2D Atlas;
        int TileWidth;
        int TileHeight;
    };
    
    Tileset LoadTileset(std::string_view filepath);
}
