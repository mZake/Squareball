#include "Collision.h"

#include <cmath>

#include <raylib.h>
#include <raymath.h>

#include "Entity.h"

namespace Squareball
{
    Intersection IntersectRectangles(Rectangle rect1, Rectangle rect2)
    {
        float rect1Left    = rect1.x;
        float rect1Right   = rect1.x + rect1.width;
        float rect1Top     = rect1.y;
        float rect1Bottom  = rect1.y + rect1.height;

        float rect2Left    = rect2.x;
        float rect2Right   = rect2.x + rect2.width;
        float rect2Top     = rect2.y;
        float rect2Bottom  = rect2.y + rect2.height;

        Intersection result = {};

        if (CheckCollisionRecs(rect1, rect2))
        {
            float left      = std::fabsf(rect1Left - rect2Right);
            float right     = std::fabsf(rect1Right - rect2Left);
            float top       = std::fabsf(rect1Top - rect2Bottom);
            float bottom    = std::fabsf(rect1Bottom - rect2Top);

            float xDepth = std::fminf(left, right);
            float yDepth = std::fminf(top, bottom);

            if (xDepth < yDepth)
            {
                if (left < right)
                {
                    result.Normal = { -1.0f, 0.0f };
                    result.Depth = left;
                }
                else
                {
                    result.Normal = { 1.0f, 0.0f };
                    result.Depth = right;
                }
            }
            else
            {
                if (top < bottom)
                {
                    result.Normal = { 0.0f, -1.0f };
                    result.Depth = top;
                }
                else
                {
                    result.Normal = { 0.0f, 1.0f };
                    result.Depth = bottom;
                }
            }

            result.Overlapping = true;
        }
        
        return result;
    }

    Intersection IntersectEntities(const Entity& entity1, const Entity& entity2)
    {
        Rectangle entity1Rect = { entity1.Position.x, entity1.Position.y, (float)entity1.Width, (float)entity1.Height };
        Rectangle entity2Rect = { entity2.Position.x, entity2.Position.y, (float)entity2.Width, (float)entity2.Height };

        return IntersectRectangles(entity1Rect, entity2Rect);
    }

    void ProcessCollisionPlayers(Player& player1, Player& player2)
    {
        Intersection intersection = IntersectEntities(player1, player2);
        if (intersection.Overlapping)
        {
            player1.Position -= intersection.Normal * intersection.Depth / 2;
            player2.Position += intersection.Normal * intersection.Depth / 2;
        }
    }

    void ProcessCollisionPlayerBall(Player& player, Ball& ball)
    {
        Intersection intersection = IntersectEntities(player, ball);
        if (intersection.Overlapping)
        {
            player.Position -= intersection.Normal * intersection.Depth;
            ball.Velocity += intersection.Normal * ball.ImpulseForce;
        }
    }
}
