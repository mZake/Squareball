#pragma once

#include <raylib.h>

#include "Entity.h"

namespace Squareball
{
    struct Intersection
    {
        Vector2     Normal;
        float       Depth;
        bool        Overlapping;
    };

    Intersection IntersectRectangles(Rectangle rect1, Rectangle rect2);

    void HandleCollisionPlayers(PlayerEntity& player1, PlayerEntity& player2);
    void HandleCollisionPlayerBall(PlayerEntity& player, BallEntity& ball);
}
