#pragma once

#include <raylib.h>

namespace Squareball
{
    struct Intersection
    {
        Vector2     normal;
        float       depth;
        bool        overlapping;
    };

    struct Entity
    {
        Vector2     position;
        Vector2     velocity;
        Color       color;
    };

    constexpr int EntityWidth = 64;
    constexpr int EntityHeight = 64;
    
    Intersection    IntersectEntities(const Entity& e1, const Entity& e2);
    void            DrawEntity(const Entity& e);
}
