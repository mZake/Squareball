#include "Entity.h"

namespace Squareball
{
    void UpdateEntityPositionX(Entity& entity)
    {
        entity.WasMovingX = entity.MovedX;
        entity.MovedX = false;
        entity.Position.x += entity.Velocity.x;
        
        if (entity.Velocity.x != 0.0f)
        {
            entity.MovedX = true;
            entity.CanMoveX = true;
        }
    }
    
    void UpdateEntityPositionY(Entity& entity)
    {
        entity.WasMovingY = entity.MovedY;
        entity.MovedY = false;
        entity.Position.y += entity.Velocity.y;
        
        if (entity.Velocity.y != 0.0f)
        {
            entity.MovedY = true;
            entity.CanMoveY = true;
        }
    }
    
    void MoveEntityX(Entity& entity, float offset)
    {
        entity.Position.x += offset;
        
        if (offset != 0.0f)
        {
            entity.MovedX = true;
            entity.CanMoveX = true;
        }
    }
    
    void MoveEntityY(Entity& entity, float offset)
    {
        entity.Position.y += offset;
        
        if (offset != 0.0f)
        {
            entity.MovedY = true;
            entity.CanMoveY = true;
        }
    }
    
    void DrawEntity(const Entity& entity)
    {
        DrawTextureV(entity.Texture, entity.Position, WHITE);
    }
}
