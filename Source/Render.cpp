#include "Render.h"

#include <raylib.h>

#include "Entity.h"

namespace Squareball
{
    void DrawPlayer(const PlayerEntity& player)
    {
        Rectangle rect = { player.Position.x, player.Position.y, (float)player.Width, (float)player.Height };
        DrawRectangleRec(rect, player.Color);
    }

    void DrawBall(const BallEntity& ball)
    {
        Rectangle rect = { ball.Position.x, ball.Position.y, (float)ball.Width, (float)ball.Height };
        DrawRectangleRec(rect, ball.Color);
    }

    void CustomDrawFPS()
    {
        int fps = GetFPS();
        const char* text = TextFormat("FPS: %d", fps);
        DrawText(text, 10, 10, 30, BLACK);
    }
}
