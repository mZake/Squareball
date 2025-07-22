#pragma once

#include <raylib.h>

namespace Squareball
{
    enum class PlayerType
    {
        None = 0,
        Local1,
        Local2,
        Bot,
    };

    struct GameEntity
    {
        Vector2     Position;
        Vector2     Velocity;
        Color       Color;
        int         Width;
        int         Height;
    };

    struct PlayerEntity : public GameEntity
    {
        PlayerType  Type;
        float       Speed;
    };

    struct BallEntity : public GameEntity
    {
        float       Friction;
        float       ImpulseForce;
    };
}
