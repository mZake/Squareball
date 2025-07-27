#pragma once

#include <raylib.h>

namespace Squareball
{
    struct Entity
    {
        Vector2     Position;
        Vector2     Velocity;
        Texture2D   Texture;
        int         Width;
        int         Height;
    };

    enum class PlayerController
    {
        None = 0,
        WASDKeys,
        ArrowKeys,
    };

    struct Player : public Entity
    {
        PlayerController    Controller;
        float               Speed;
    };

    struct Ball : public Entity
    {
        float Friction;
        float ImpulseForce;
    };

    void MoveEntityX(Entity& entity);
    void MoveEntityY(Entity& entity);

    void UpdatePlayer(Player& player, float delta);
    void UpdateBall(Ball& ball, float delta);

    void DrawEntity(const Entity& entity);
}
