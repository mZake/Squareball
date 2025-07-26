#include "Game.h"

#include <raylib.h>

#include "Scenes/Match.h"

namespace Squareball
{
    struct Context
    {
        UpdateCallback OnUpdate;
        RenderCallback OnRender;
    };

    static Context s_Context = {};

    void SetGameUpdateCallback(UpdateCallback cb)
    {
        s_Context.OnUpdate = cb;
    }

    void SetGameRenderCallback(RenderCallback cb)
    {
        s_Context.OnRender = cb;
    }

    void GameMain()
    {
        InitWindow(1152, 640, "Squareball");

        InitMatchScene();

        while (!WindowShouldClose())
        {
            float delta = GetFrameTime();

            s_Context.OnUpdate(delta);

            BeginDrawing();
            s_Context.OnRender();
            EndDrawing();
        }

        CloseWindow();
    }
}
