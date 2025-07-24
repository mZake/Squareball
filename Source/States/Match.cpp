#include "Match.h"

#include <raylib.h>
#include <raymath.h>

#include "Collision.h"
#include "State.h"

constexpr int WindowWidth = 1152;
constexpr int WindowHeight = 648;

namespace Squareball
{
    static void CustomDrawFPS()
    {
        int fps = GetFPS();
        const char* text = TextFormat("FPS: %d", fps);
        DrawText(text, 10, 10, 30, BLACK);
    }

    GameState RunMatch()
    {
        Player player = {};
        player.Color = RED;
        player.Width = 64;
        player.Height = 64;
        player.Controller = PlayerController::WASDKeys;
        player.Speed = 300.0f;

        Player bot = {};
        bot.Position = { 300.0f, 300.0f };
        bot.Color = BLUE;
        bot.Width = 64;
        bot.Height = 64;
        bot.Controller = PlayerController::None;
        bot.Speed = 300.0f;

        Ball ball = {};
        ball.Position = { 100.0f, 100.0f };
        ball.Color = WHITE;
        ball.Width = 48;
        ball.Height = 48;
        ball.Friction = 0.2f;
        ball.ImpulseForce = 8.0f;

        while (!WindowShouldClose())
        {
            float delta = GetFrameTime();

            UpdatePlayer(player, delta);
            UpdateBall(ball, delta);

            MoveEntityX(player);
            MoveEntityY(player);
            MoveEntityX(ball);
            MoveEntityY(ball);
            
            BeginDrawing();

            ClearBackground(GREEN);

            DrawEntity(player);
            DrawEntity(bot);
            DrawEntity(ball);
            CustomDrawFPS();

            EndDrawing();
        }

        return GameState::None;
    }
}
