#include "Entity.h"

namespace Squareball
{
    void MoveEntityX(Entity& entity)
    {
        entity.Position.x += entity.Velocity.x;
    }
    
    void MoveEntityY(Entity& entity)
    {
        entity.Position.y += entity.Velocity.y;
    }
    
    void DrawEntity(const Entity& entity)
    {
        DrawTextureV(entity.Texture, entity.Position, WHITE);
    }
}
