#include "Game.h"

#include <cmath>

#include <raylib.h>

#include "Scenes/Match.h"

namespace Squareball
{
    static Rectangle GetRenderTargetDestination();

    constexpr int WindowWidth = 1152;
    constexpr int WindowHeight = 640;

    struct Context
    {
        UpdateCallback  OnUpdate;
        RenderCallback  OnRender;
        RenderTexture2D RenderTarget;
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
        InitWindow(WindowWidth, WindowHeight, "Squareball");
        SetWindowState(FLAG_WINDOW_RESIZABLE);

        InitMatchScene();

        s_Context.RenderTarget = LoadRenderTexture(WindowWidth, WindowHeight);
        SetTextureFilter(s_Context.RenderTarget.texture, TEXTURE_FILTER_POINT);

        while (!WindowShouldClose())
        {
            float delta = GetFrameTime();

            s_Context.OnUpdate(delta);

            BeginTextureMode(s_Context.RenderTarget);
            s_Context.OnRender();
            EndTextureMode();

            BeginDrawing();

            ClearBackground(BLACK);

            Texture2D targetTexture = s_Context.RenderTarget.texture;
            Rectangle source = { 0.0f, 0.0f, (float)targetTexture.width, (float)-targetTexture.height };
            Rectangle destination = GetRenderTargetDestination();
            DrawTexturePro(targetTexture, source, destination, { 0.0f, 0.0f }, 0.0f, WHITE);

            EndDrawing();
        }

        UnloadRenderTexture(s_Context.RenderTarget);
        CloseWindow();
    }

    static Rectangle GetRenderTargetDestination()
    {
        float scale = std::fminf((float)GetScreenWidth() / WindowWidth, (float)GetScreenHeight() / WindowHeight);

        return Rectangle {
            (GetScreenWidth() - ((float)WindowWidth * scale)) * 0.5f,
            (GetScreenHeight() - ((float)WindowHeight * scale)) * 0.5f,
            (float)WindowWidth * scale,
            (float)WindowHeight * scale,
        };
    }
}
