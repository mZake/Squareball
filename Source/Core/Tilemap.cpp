#include "Core/Tilemap.h"

#include "Core/Tileset.h"

#include <yaml-cpp/yaml.h>

namespace Squareball
{
    Tilemap LoadTilemap(std::string_view filepath, Tileset& tileset)
    {
        YAML::Node node = YAML::LoadFile(filepath.data());
        
        Tilemap tilemap;
        tilemap.Tiles = node["Tiles"].as<std::vector<int>>();
        tilemap.TilesetPtr = &tileset;
        tilemap.Width = node["Width"].as<int>();
        tilemap.Height = node["Height"].as<int>();
        
        return tilemap;
    }
    
    void DrawTilemap(const Tilemap& tilemap)
    {
        Tileset& tileset = *tilemap.TilesetPtr;
        
        for (int y = 0; y < tilemap.Height; y++)
        {
            for (int x = 0; x < tilemap.Width; x++)
            {
                int tileIndex = tilemap.Tiles[x + y * tilemap.Width];
                Tile tile = tileset.Tiles[tileIndex];
                
                Rectangle source = { tile.TexCoords.x, tile.TexCoords.y, (float)tileset.TileWidth, (float)tileset.TileHeight };
                Vector2 position = { (float)x * tileset.TileWidth, (float)y * tileset.TileHeight };
                DrawTextureRec(tileset.Atlas, source, position, WHITE);
            }
        }
    }
}
