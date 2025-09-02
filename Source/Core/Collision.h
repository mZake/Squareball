#pragma once

#include "Core/Entity.h"
#include "Core/Tilemap.h"

#include <raylib.h>

namespace Squareball
{
    struct Intersection
    {
        Vector2 Normal;
        float Depth;
        bool Overlapping;
    };
    
    Intersection IntersectRectangles(Rectangle rect1, Rectangle rect2);
    Intersection IntersectEntities(const Entity& entity1, const Entity& entity2);
    Intersection IntersectRectangleTilemap(Rectangle rect, const Tilemap& map);
    Intersection IntersectEntityTilemap(const Entity& entity, const Tilemap& map);
}
