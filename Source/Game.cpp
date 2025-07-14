#include <raylib.h>

#include "State.h"

namespace Squareball
{
    void GameMain()
    {
        InitWindow(1152, 648, "Squareball");

        GameState state = GameState::Placeholder;

        while (!WindowShouldClose())
        {
            state = RunState(state);

            // TODO: Remove this
            BeginDrawing();
            ClearBackground(RED);
            EndDrawing();
        }

        CloseWindow();
    }
}
