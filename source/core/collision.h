#pragma once

#include "core/entity.h"
#include "core/tilemap.h"

#include <raylib.h>

namespace Squareball
{
    enum class Axis { X, Y };
    
    struct Intersection
    {
        Vector2 Normal;
        float Depth;
        bool Overlapping;
    };
    
    Intersection IntersectRectangles(Rectangle rect1, Rectangle rect2, Axis axis);
    Intersection IntersectEntities(const Entity& entity1, const Entity& entity2, Axis axis);
    Intersection IntersectRectangleTilemap(Rectangle rect, const Tilemap& map, Axis axis);
    Intersection IntersectEntityTilemap(const Entity& entity, const Tilemap& map, Axis axis);
}
