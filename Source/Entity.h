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

    struct PlayerEntity
    {
        PlayerType  Type;
        Vector2     Position;
        Color       Color;
        int         Width;
        int         Height;
        float       Speed;
    };

    struct BallEntity
    {
        Vector2     Position;
        Vector2     Velocity;
        Color       Color;
        int         Width;
        int         Height;
        float       Friction;
        float       ImpulseForce;
    };
}
