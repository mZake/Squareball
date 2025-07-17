#include "Entity.h"

#include <cmath>

namespace Squareball
{
    Intersection IntersectEntities(const Entity& e1, const Entity& e2)
    {
        float e1Left    = e1.position.x;
        float e1Right   = e1.position.x + EntityWidth;
        float e1Top     = e1.position.y;
        float e1Bottom  = e1.position.y + EntityHeight;

        float e2Left    = e2.position.x;
        float e2Right   = e2.position.x + EntityWidth;
        float e2Top     = e2.position.y;
        float e2Bottom  = e2.position.y + EntityHeight;

        Intersection result = {};

        if (e1Left <= e2Right && e1Right >= e2Left &&
            e1Top <= e2Bottom && e1Bottom >= e2Top)
        {
            float left      = std::fabsf(e1Left - e2Right);
            float right     = std::fabsf(e1Right - e2Left);
            float top       = std::fabsf(e1Top - e2Bottom);
            float bottom    = std::fabsf(e1Bottom - e2Top);

            float xDepth = std::fabs(std::fminf(left, right));
            float yDepth = std::fabs(std::fminf(top, bottom));

            if (xDepth < yDepth)
            {
                if (left < right)
                {
                    result.normal = { -1.0f, 0.0f };
                    result.depth = left;
                }
                else
                {
                    result.normal = { 1.0f, 0.0f };
                    result.depth = right;
                }
            }
            else
            {
                if (top < bottom)
                {
                    result.normal = { 0.0f, -1.0f };
                    result.depth = top;
                }
                else
                {
                    result.normal = { 0.0f, 1.0f };
                    result.depth = bottom;
                }
            }

            result.overlapping = true;
        }

        return result;
    }

    void DrawEntity(const Entity& e)
    {
        DrawRectangleV(e.position, Vector2{ EntityWidth, EntityHeight }, e.color);
    }
}
