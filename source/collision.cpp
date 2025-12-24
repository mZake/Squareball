#include "collision.h"

#include "entity.h"
#include "tilemap.h"

#include <raylib.h>
#include <raymath.h>

#include <float.h>
#include <math.h>

namespace Squareball
{
    constexpr float MaxDepth = 1000000000.0f;
    
    Intersection IntersectRectangles(Rectangle rect1, Rectangle rect2, Axis axis)
    {
        if (!CheckCollisionRecs(rect1, rect2))
            return Intersection{};
        
        Intersection intersection = {};
        
        if (axis == Axis::X)
        {
            float rect1Left = rect1.x;
            float rect1Right = rect1.x + rect1.width;
            float rect2Left = rect2.x;
            float rect2Right = rect2.x + rect2.width;
            
            if (rect1Left <= rect2Right && rect1Right >= rect2Left)
            {
                float left = fabsf(rect1Left - rect2Right);
                float right = fabsf(rect1Right - rect2Left);
                
                if (left < right)
                {
                    intersection.Normal = { -1.0f, 0.0f };
                    intersection.Depth = left;
                }
                else
                {
                    intersection.Normal = { 1.0f, 0.0f };
                    intersection.Depth = right;
                }
                
                intersection.Overlapping = true;
            }
        }
        else if (axis == Axis::Y)
        {
            float rect1Top = rect1.y;
            float rect1Bottom = rect1.y + rect1.height;
            float rect2Top = rect2.y;
            float rect2Bottom = rect2.y + rect2.height;
            
            if (rect1Top <= rect2Bottom && rect1Bottom >= rect2Top)
            {
                float top = fabsf(rect1Top - rect2Bottom);
                float bottom = fabsf(rect1Bottom - rect2Top);
                
                if (top < bottom)
                {
                    intersection.Normal = { 0.0f, -1.0f };
                    intersection.Depth = top;
                }
                else
                {
                    intersection.Normal = { 0.0f, 1.0f };
                    intersection.Depth = bottom;
                }
                
                intersection.Overlapping = true;
            }
        }
        
        return intersection;
    }
    
    Intersection IntersectEntities(const Entity& entity1, const Entity& entity2, Axis axis)
    {
        Rectangle entity1Rect = { entity1.Position.x, entity1.Position.y, (float)entity1.Width, (float)entity1.Height };
        Rectangle entity2Rect = { entity2.Position.x, entity2.Position.y, (float)entity2.Width, (float)entity2.Height };
        
        return IntersectRectangles(entity1Rect, entity2Rect, axis);
    }
    
    Intersection IntersectRectangleTilemap(Rectangle rect, const Tilemap& tilemap, Axis axis)
    {
        Tileset& tileset = *tilemap.TilesetPtr;
        
        int rectLeft = rect.x;
        int rectRight = rect.x + rect.width;
        int rectTop = rect.y;
        int rectBottom = rect.y + rect.height;
        
        int leftTile = rectLeft / tileset.TileWidth;
        int rightTile = rectRight / tileset.TileWidth;
        int topTile = rectTop / tileset.TileHeight;
        int bottomTile = rectBottom / tileset.TileHeight;
        
        Intersection intersection = {};
        intersection.Depth = FLT_MAX;
        
        for (int y = topTile; y <= bottomTile; y++)
        {
            for (int x = leftTile; x <= rightTile; x++)
            {
                int tileIndex = tilemap.Tiles[x + y * tilemap.Width];
                Tile tile = tileset.Tiles[tileIndex];
                if (tile.Flags & TileFlags_Wall)
                {
                    Rectangle tileRect = {
                        (float)x * tileset.TileWidth, (float)y * tileset.TileHeight,
                        (float)tileset.TileWidth, (float)tileset.TileHeight,
                    };
                    
                    Intersection tileIntersection = IntersectRectangles(rect, tileRect, axis);
                    if (tileIntersection.Overlapping && tileIntersection.Depth < intersection.Depth)
                        intersection = tileIntersection;
                }
            }
        }
        
        return intersection;
    }
    
    Intersection IntersectEntityTilemap(const Entity& entity, const Tilemap& map, Axis axis)
    {
        Rectangle entityRect = { entity.Position.x, entity.Position.y, (float)entity.Width, (float)entity.Height };
        
        return IntersectRectangleTilemap(entityRect, map, axis);
    }
}
