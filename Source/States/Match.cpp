#include "Match.h"

#include <raylib.h>
#include <raymath.h>

constexpr int       WindowWidth = 1152;
constexpr int       WindowHeight = 648;
constexpr float     MoveSpeed = 400.0f;
constexpr float     BallFriction = 0.3f;

namespace Squareball
{
    static void UpdatePlayer(Entity& player, float delta);
    static void UpdateBall(Entity& ball, float delta);
    static void IntersectPlayerBall(Entity& player, Entity& ball, float delta);

    GameState RunMatch()
    {
        Entity player = {
            .position = { 0.0f, 0.0f },
            .velocity = { 0.0f, 0.0f },
            .color = RED,
        };

        Entity ball = {
            .position = { 100.0f, 100.0f },
            .velocity = { 0.0f, 0.0f },
            .color = WHITE,
        };

        while (!WindowShouldClose())
        {
            float delta = GetFrameTime();

            UpdatePlayer(player, delta);
            UpdateBall(ball, delta);
            IntersectPlayerBall(player, ball, delta);
            
            BeginDrawing();

            ClearBackground(GREEN);
            DrawEntity(player);
            DrawEntity(ball);

            EndDrawing();
        }

        return GameState::None;
    }

    static void UpdatePlayer(Entity& player, float delta)
    {
        Vector2 direction = {
            .x = (float)((int)IsKeyDown(KEY_D) - (int)IsKeyDown(KEY_A)),
            .y = (float)((int)IsKeyDown(KEY_S) - (int)IsKeyDown(KEY_W)),
        };

        direction = Vector2Normalize(direction);
        player.velocity = direction * MoveSpeed * delta;
        player.position += player.velocity;

        player.position.x = Clamp(player.position.x, 0, WindowWidth - EntityWidth);
        player.position.y = Clamp(player.position.y, 0, WindowHeight - EntityHeight);
    }

    static void UpdateBall(Entity& ball, float delta)
    {
        if (ball.velocity != Vector2Zero())
        {
            ball.velocity -= ball.velocity * BallFriction * delta;
            ball.position += ball.velocity;
            if (ball.position.x < 0 || ball.position.x > WindowWidth - EntityWidth)
            {
                ball.position.x = Clamp(ball.position.x, 0, WindowWidth - EntityWidth);
                ball.velocity.x *= -1;
            }
            if (ball.position.y < 0 || ball.position.y > WindowHeight - EntityHeight)
            {
                ball.position.y = Clamp(ball.position.y, 0, WindowHeight - EntityHeight);
                ball.velocity.y *= -1;
            }
        }
    }

    static void IntersectPlayerBall(Entity& player, Entity& ball, float delta)
    {
        Intersection result = IntersectEntities(player, ball);
        if (result.overlapping)
        {
            player.position -= result.normal * result.depth;
            ball.velocity += result.normal * 500.0f * delta;
        }
    }
}
