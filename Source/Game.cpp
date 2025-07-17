#include <raylib.h>

#include "State.h"

namespace Squareball
{
    void GameMain()
    {
        InitWindow(1152, 648, "Squareball");

        GameState state = GameState::Match;

        while (!WindowShouldClose())
        {
            state = RunState(state);
        }

        CloseWindow();
    }
}
