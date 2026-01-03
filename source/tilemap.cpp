#include <SDL3/SDL.h>

#include <fstream>
#include <vector>

#include <stdint.h>

#include "tilemap.h"

namespace Squareball
{
#pragma pack(push, 1)
    struct SBMHeader
    {
        uint8_t magic[4];
        int32_t width;
        int32_t height;
    };
    
    struct SBMCell
    {
        int32_t tile_x;
        int32_t tile_y;
        uint32_t flags;
    };
#pragma pack(pop)
    
    constexpr size_t SBM_MINIMUM_SIZE = sizeof(SBMHeader) + sizeof(SBMCell);
    
    Tileset CreateTileset(SDL_Texture* atlas, int32_t tile_width, int32_t tile_height)
    {
        SDL_assert(atlas != nullptr);
        SDL_assert(tile_width >= 4);
        SDL_assert(tile_height >= 4);
        
        float atlas_width, atlas_height;
        SDL_GetTextureSize(atlas, &atlas_width, &atlas_height);
        
        Tileset tileset;
        tileset.atlas = atlas;
        tileset.tile_width = tile_width;
        tileset.tile_height = tile_height;
        tileset.width = static_cast<int32_t>(atlas_width) / tile_width;
        tileset.height = static_cast<int32_t>(atlas_height) / tile_height;
        
        return tileset;
    }
    
    Tilemap LoadTilemap(const Tileset& tileset, const char* filepath)
    {
        SDL_assert(filepath != nullptr);
        
        std::ifstream stream(filepath, std::ios::binary);
        if (!stream)
            return {};
        
        stream.seekg(0, std::ios::end);
        size_t stream_size = stream.tellg();
        if (stream_size < SBM_MINIMUM_SIZE)
            return {};
        
        stream.seekg(0, std::ios::beg);
        SBMHeader sbm_header;
        stream.read(reinterpret_cast<char*>(&sbm_header), sizeof(SBMHeader));
        
        if (memcmp(sbm_header.magic, "SBMP", 4) != 0)
            return {};
        
        size_t sbm_cells_begin = stream.tellg();
        size_t sbm_cell_count = sbm_header.width * sbm_header.height;
        size_t sbm_cells_size = sbm_cell_count * sizeof(SBMCell);
        size_t sbm_cells_real_size = stream_size - sbm_cells_begin;
        
        if (sbm_cells_real_size != sbm_cells_size)
            return {};
        
        stream.seekg(sbm_cells_begin, std::ios::beg);
        std::vector<SBMCell> sbm_cells(sbm_cell_count);
        stream.read(reinterpret_cast<char*>(sbm_cells.data()), sbm_cells_size);
        
        std::vector<MapCell> map_cells(sbm_cell_count);
        
        for (size_t i = 0; i < sbm_cell_count; i++)
        {
            MapCell& map_cell = map_cells[i];
            SBMCell& sbm_cell = sbm_cells[i];
            
            map_cell.tile_x = sbm_cell.tile_x;
            map_cell.tile_y = sbm_cell.tile_y;
            map_cell.flags = sbm_cell.flags;
        }
        
        stream.close();
        
        Tilemap tilemap;
        tilemap.tileset = &tileset;
        tilemap.cells = std::move(map_cells);
        tilemap.width = sbm_header.width;
        tilemap.height = sbm_header.height;
        
        return tilemap;
    }
    
    MapCell GetTilemapCell(const Tilemap& tilemap, int32_t cell_x, int32_t cell_y)
    {
        SDL_assert(cell_x >= 0);
        SDL_assert(cell_y >= 0);
        
        return tilemap.cells[cell_x + cell_y * tilemap.width];
    }
    
    void DrawTilemap(SDL_Renderer* renderer, const Tilemap& tilemap)
    {
        SDL_assert(renderer != nullptr);
        
        const Tileset& tileset = *tilemap.tileset;
        
        for (int32_t y = 0; y < tilemap.height; y++)
        {
            for (int32_t x = 0; x < tilemap.width; x++)
            {
                MapCell map_cell = GetTilemapCell(tilemap, x, y);
                
                SDL_FRect source_rect;
                source_rect.x = map_cell.tile_x * tileset.tile_width;
                source_rect.y = map_cell.tile_y * tileset.tile_height;
                source_rect.w = tileset.tile_width;
                source_rect.h = tileset.tile_height;
                
                SDL_FRect dest_rect;
                dest_rect.x = x * tileset.tile_width;
                dest_rect.y = y * tileset.tile_height;
                dest_rect.w = tileset.tile_width;
                dest_rect.h = tileset.tile_height;
                
                SDL_RenderTexture(renderer, tileset.atlas, &source_rect, &dest_rect);
            }
        }
    }
}
