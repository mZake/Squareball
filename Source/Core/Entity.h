#pragma once

#include <raylib.h>

namespace Squareball
{
    struct Entity
    {
        Texture2D Texture;
        Vector2 Position;
        Vector2 Velocity;
        int Width, Height;
        bool WasMovingX, WasMovingY;
        bool MovedX, MovedY;
        bool CanMoveX, CanMoveY;
    };
    
    void UpdateEntityPositionX(Entity& entity);
    void UpdateEntityPositionY(Entity& entity);
    
    void MoveEntityX(Entity& entity, float offset);
    void MoveEntityY(Entity& entity, float offset);
    
    void DrawEntity(const Entity& entity);
}
