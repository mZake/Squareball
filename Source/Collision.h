#pragma once

#include <raylib.h>

#include "Entity.h"
#include "Tilemap.h"

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
    Intersection IntersectRectangleTilemap(Rectangle rect, const Tilemap& map);
    Intersection IntersectEntityTilemap(const Entity& entity, const Tilemap& map);

    void ProcessCollisionPlayers(Player& player1, Player& player2);
    void ProcessCollisionPlayerBall(Player& player, Ball& ball);
    void ProcessCollisionPlayerTilemap(Player& player, const Tilemap& map);
    void ProcessCollisionBallTilemap(Ball& ball, const Tilemap& map);
}
