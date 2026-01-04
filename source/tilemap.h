#pragma once

#include <vector>

#include <SDL3/SDL.h>

#include "core.h"
#include "texture.h"

namespace Squareball
{
    enum TileFlags : uint32
    {
        TileFlagsNone       = 0,
        TileFlagsWall       = 1 << 0,
        TileFlagsLeftGoal   = 1 << 1,
        TileFlagsRightGoal  = 1 << 2,
    };
    
    struct MapCell
    {
        int32 tile_x;
        int32 tile_y;
        uint32 flags;
    };
    
    struct Tileset
    {
        TextureID atlas_id;
        int32 tile_width;
        int32 tile_height;
        int32 width;
        int32 height;
    };
    
    struct Tilemap
    {
        std::vector<MapCell> cells;
        Tileset tileset;
        int32 width;
        int32 height;
    };
    
    Tileset CreateTileset(TextureID atlas_id, int32 tile_width, int32 tile_height);
    Tilemap LoadTilemap(const Tileset& tileset, const char* filepath);
    MapCell GetTilemapCell(const Tilemap& tilemap, int32 cell_x, int32 cell_y);
    void DrawTilemap(SDL_Renderer* renderer, const Tilemap& tilemap);
}
