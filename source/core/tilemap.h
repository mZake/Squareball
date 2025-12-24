#pragma once

#include "core/tileset.h"

#include <raylib.h>

#include <string_view>
#include <vector>

namespace Squareball
{
    struct Tilemap
    {
        std::vector<int> Tiles;
        Tileset* TilesetPtr;
        int Width;
        int Height;
    };
    
    Tilemap LoadTilemap(std::string_view filepath, Tileset& tileset);
    void DrawTilemap(const Tilemap& tilemap);
}
