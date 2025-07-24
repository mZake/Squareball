#pragma once

namespace Squareball
{
    enum class GameState
    {
        None = 0,
        Match,
    };

    GameState RunState(GameState state);
}
