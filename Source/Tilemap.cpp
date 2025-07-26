#include "Tilemap.h"

namespace Squareball
{
    void DrawTilemap(const Tilemap& map)
    {
        int tileWidth = map.Tileset.TileWidth;
        int tileHeight = map.Tileset.TileHeight;

        for (int y = 0; y < map.Height; y++)
        {
            for (int x = 0; x < map.Width; x++)
            {
                int tileIndex = map.Tiles[x + y * map.Width];
                Tile tile = map.Tileset.Tiles[tileIndex];

                Rectangle source = { tile.TexCoords.x, tile.TexCoords.y, (float)tileWidth, (float)tileHeight };
                Vector2 position = { (float)x * tileWidth, (float)y * tileHeight };
                DrawTextureRec(map.Tileset.Atlas, source, position, WHITE);
            }
        }
    }
}
