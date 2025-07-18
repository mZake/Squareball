#include "Match.h"

#include <string>

#include <raylib.h>
#include <raymath.h>

#include "Collision.h"
#include "State.h"

constexpr int WindowWidth = 1152;
constexpr int WindowHeight = 648;

namespace Squareball
{
    static void UpdatePlayer(PlayerEntity& player, float delta);
    static void UpdateBall(BallEntity& ball, float delta);

    static void DrawPlayer(const PlayerEntity& player);
    static void DrawBall(const BallEntity& ball);
    static void CustomDrawFPS();

    GameState RunMatch()
    {
        PlayerEntity player = {
            .Type       = PlayerType::Local1,
            .Position   = { 0.0f, 0.0f },
            .Color      = RED,
            .Width      = 64,
            .Height     = 64,
            .Speed      = 300.0f,
        };

        PlayerEntity bot = {
            .Type       = PlayerType::Bot,
            .Position   = { 300.0f, 300.0f },
            .Color      = BLUE,
            .Width      = 64,
            .Height     = 64,
            .Speed      = 300.0f,
        };

        BallEntity ball = {
            .Position       = { 100.0f, 100.0f },
            .Velocity       = { 0.0f, 0.0f },
            .Color          = WHITE,
            .Width          = 48,
            .Height         = 48,
            .Friction       = 0.2f,
            .ImpulseForce   = 500.0f,
        };

        while (!WindowShouldClose())
        {
            float delta = GetFrameTime();

            UpdatePlayer(player, delta);
            UpdateBall(ball, delta);

            HandleCollisionPlayers(player, bot);
            HandleCollisionPlayerBall(player, ball);
            HandleCollisionPlayerBall(bot, ball);
            
            BeginDrawing();

            ClearBackground(GREEN);

            DrawPlayer(player);
            DrawPlayer(bot);
            DrawBall(ball);
            CustomDrawFPS();

            EndDrawing();
        }

        return GameState::None;
    }

    static void UpdatePlayer(PlayerEntity& player, float delta)
    {
        Vector2 direction = {
            .x = (float)((int)IsKeyDown(KEY_D) - (int)IsKeyDown(KEY_A)),
            .y = (float)((int)IsKeyDown(KEY_S) - (int)IsKeyDown(KEY_W)),
        };

        direction = Vector2Normalize(direction);
        player.Position += direction * player.Speed * delta;

        player.Position.x = Clamp(player.Position.x, 0, WindowWidth - player.Width);
        player.Position.y = Clamp(player.Position.y, 0, WindowHeight - player.Height);
    }

    static void UpdateBall(BallEntity& ball, float delta)
    {
        if (ball.Velocity != Vector2Zero())
        {
            ball.Velocity -= ball.Velocity * ball.Friction * delta;
            ball.Position += ball.Velocity;

            if (ball.Position.x < 0 || ball.Position.x > WindowWidth - ball.Width)
            {
                ball.Position.x = Clamp(ball.Position.x, 0, WindowWidth - ball.Width);
                ball.Velocity.x *= -1;
            }
            if (ball.Position.y < 0 || ball.Position.y > WindowHeight - ball.Height)
            {
                ball.Position.y = Clamp(ball.Position.y, 0, WindowHeight - ball.Height);
                ball.Velocity.y *= -1;
            }
        }
    }

    static void DrawPlayer(const PlayerEntity& player)
    {
        Rectangle rect = { player.Position.x, player.Position.y, (float)player.Width, (float)player.Height };
        DrawRectangleRec(rect, player.Color);
    }

    static void DrawBall(const BallEntity& ball)
    {
        Rectangle rect = { ball.Position.x, ball.Position.y, (float)ball.Width, (float)ball.Height };
        DrawRectangleRec(rect, ball.Color);
    }

    static void CustomDrawFPS()
    {
        int fps = GetFPS();
        const char* text = TextFormat("FPS: %d", fps);
        DrawText(text, 10, 10, 30, BLACK);
    }
}
