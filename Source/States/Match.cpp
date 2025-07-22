#include "Match.h"

#include <raylib.h>
#include <raymath.h>

#include "Collision.h"
#include "State.h"
#include "Render.h"

constexpr int WindowWidth = 1152;
constexpr int WindowHeight = 648;

namespace Squareball
{
    static void UpdatePlayer(PlayerEntity& player, float delta);
    static void UpdateBall(BallEntity& ball, float delta);
    
    GameState RunMatch()
    {
        PlayerEntity player = {};
        player.Color = RED;
        player.Width = 64;
        player.Height = 64;
        player.Type = PlayerType::Local1;
        player.Speed = 300.0f;

        PlayerEntity bot = {};
        bot.Position = { 300.0f, 300.0f };
        bot.Color = BLUE;
        bot.Width = 64;
        bot.Height = 64;
        bot.Type = PlayerType::Bot;
        bot.Speed = 300.0f;

        BallEntity ball = {};
        ball.Position = { 100.0f, 100.0f };
        ball.Color = WHITE;
        ball.Width = 48;
        ball.Height = 48;
        ball.Friction = 0.2f;
        ball.ImpulseForce = 500.0f;

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

            DrawEntity(player);
            DrawEntity(bot);
            DrawEntity(ball);
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
}
