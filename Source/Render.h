#pragma once

#include <raylib.h>

#include "Entity.h"

namespace Squareball
{
    void DrawPlayer(const PlayerEntity& player);
    void DrawBall(const BallEntity& ball);
    void CustomDrawFPS();
}
