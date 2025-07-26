#pragma once

#include <stdint.h>

#include <vector>

#include <raylib.h>

namespace Squareball
{
    enum TileFlags : uint8_t
    {
        TileFlags_None = 0,
        TileFlags_Wall = 1 << 0,
    };

    struct Tile
    {
        Vector2     TexCoords;
        uint8_t     Flags;
    };

    struct Tileset
    {
        int                 TileWidth;
        int                 TileHeight;
        Texture2D           Atlas;
        std::vector<Tile>   Tiles;
    };

    struct Tilemap
    {
        int                 Width;
        int                 Height;
        Tileset             Tileset;
        std::vector<int>    Tiles;
    };

    void DrawTilemap(const Tilemap& map);
}
