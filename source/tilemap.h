#pragma once

#include <stdint.h>

#include <vector>

#include <SDL3/SDL.h>

namespace Squareball
{
    enum TileFlags : uint32_t
    {
        TileFlagsNone       = 0,
        TileFlagsWall       = 1 << 0,
        TileFlagsLeftGoal   = 1 << 1,
        TileFlagsRightGoal  = 1 << 2,
    };
    
    struct MapCell
    {
        int32_t tile_x;
        int32_t tile_y;
        uint32_t flags;
    };
    
    struct Tileset
    {
        SDL_Texture* atlas;
        int32_t tile_width;
        int32_t tile_height;
        int32_t width;
        int32_t height;
    };
    
    struct Tilemap
    {
        const Tileset* tileset;
        std::vector<MapCell> cells;
        int32_t width;
        int32_t height;
    };
    
    Tileset CreateTileset(SDL_Texture* atlas, int32_t tile_width, int32_t tile_height);
    Tilemap LoadTilemap(const Tileset& tileset, const char* filepath);
    MapCell GetTilemapCell(const Tilemap& tilemap, int32_t cell_x, int32_t cell_y);
    void DrawTilemap(SDL_Renderer* renderer, const Tilemap& tilemap);
}
