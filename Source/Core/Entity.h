#pragma once

#include <raylib.h>

namespace Squareball
{
    struct Entity
    {
        Texture2D Texture;
        Vector2 Position;
        Vector2 Velocity;
        int Width;
        int Height;
    };
    
    void MoveEntityX(Entity& entity);
    void MoveEntityY(Entity& entity);
    void DrawEntity(const Entity& entity);
}
