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
    Intersection IntersectEntities(const Entity& entity1, const Entity& entity2);

    void ProcessCollisionPlayers(Player& player1, Player& player2);
    void ProcessCollisionPlayerBall(Player& player, Ball& ball);
}
