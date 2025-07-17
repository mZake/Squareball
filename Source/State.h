#pragma once

namespace Squareball
{
    enum class GameState
    {
        None,
        Match,
    };

    GameState RunState(GameState state);
}
