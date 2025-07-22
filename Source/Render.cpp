#include "Render.h"

#include <raylib.h>

#include "Entity.h"

namespace Squareball
{
    void DrawEntity(const GameEntity& entity)
    {
        Rectangle rect = { entity.Position.x, entity.Position.y, (float)entity.Width, (float)entity.Height };
        DrawRectangleRec(rect, entity.Color);
    }

    void CustomDrawFPS()
    {
        int fps = GetFPS();
        const char* text = TextFormat("FPS: %d", fps);
        DrawText(text, 10, 10, 30, BLACK);
    }
}
