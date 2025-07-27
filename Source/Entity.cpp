#include "Entity.h"

#include <raylib.h>
#include <raymath.h>

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

    void UpdatePlayer(Player& player, float delta)
    {
        Vector2 direction = {};

        if (player.Controller == PlayerController::WASDKeys)
        {
            direction.x = (int)IsKeyDown(KEY_D) - (int)IsKeyDown(KEY_A);
            direction.y = (int)IsKeyDown(KEY_S) - (int)IsKeyDown(KEY_W);
        }
        else if (player.Controller == PlayerController::ArrowKeys)
        {
            direction.x = (int)IsKeyDown(KEY_RIGHT) - (int)IsKeyDown(KEY_LEFT);
            direction.y = (int)IsKeyDown(KEY_DOWN) - (int)IsKeyDown(KEY_UP);
        }

        if (direction != Vector2Zero())
            direction = Vector2Normalize(direction);

        player.Velocity = direction * player.Speed * delta;
    }

    void UpdateBall(Ball& ball, float delta)
    {
        if (ball.Velocity != Vector2Zero())
            ball.Velocity -= ball.Velocity * ball.Friction * delta;
    }

    void DrawEntity(const Entity& entity)
    {
        DrawTextureV(entity.Texture, entity.Position, WHITE);
    }
}
