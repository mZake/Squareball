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

    void HandleCollisionPlayers(PlayerEntity& player1, PlayerEntity& player2)
    {
        Rectangle player1Rect = { player1.Position.x, player1.Position.y, (float)player1.Width, (float)player1.Height };
        Rectangle player2Rect = { player2.Position.x, player2.Position.y, (float)player2.Width, (float)player2.Height };

        Intersection intersection = IntersectRectangles(player1Rect, player2Rect);
        if (intersection.Overlapping)
        {
            player1.Position -= intersection.Normal * intersection.Depth / 2;
            player2.Position += intersection.Normal * intersection.Depth / 2;
        }
    }

    void HandleCollisionPlayerBall(PlayerEntity& player, BallEntity& ball)
    {
        Rectangle playerRect = { player.Position.x, player.Position.y, (float)player.Width, (float)player.Height };
        Rectangle ballRect = { ball.Position.x, ball.Position.y, (float)ball.Width, (float)ball.Height };

        Intersection intersection = IntersectRectangles(playerRect, ballRect);
        if (intersection.Overlapping)
        {
            float delta = GetFrameTime();

            player.Position -= intersection.Normal * intersection.Depth;
            ball.Velocity += intersection.Normal * ball.ImpulseForce * delta;
        }
    }
}
