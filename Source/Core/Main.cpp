#include <raylib.h>

#include <cmath>

namespace Squareball
{
    extern void OnGameInit();
    extern void OnGameUpdate();
    extern void OnGameRender();
    
    static Rectangle GetRenderTargetDestination();
    
    constexpr int WindowWidth = 1152;
    constexpr int WindowHeight = 640;
    
    void Main()
    {
        SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
        InitWindow(WindowWidth, WindowHeight, "Squareball");
        
        OnGameInit();
        
        RenderTexture2D renderTarget = LoadRenderTexture(WindowWidth, WindowHeight);
        SetTextureFilter(renderTarget.texture, TEXTURE_FILTER_POINT);
        
        while (!WindowShouldClose())
        {
            OnGameUpdate();
            
            BeginTextureMode(renderTarget);
            OnGameRender();
            EndTextureMode();
            
            BeginDrawing();
            
            ClearBackground(BLACK);
            
            Rectangle source = { 0.0f, 0.0f, (float)renderTarget.texture.width, (float)-renderTarget.texture.height };
            Rectangle dest = GetRenderTargetDestination();
            DrawTexturePro(renderTarget.texture, source, dest, { 0.0f, 0.0f }, 0.0f, WHITE);
            
            EndDrawing();
        }
        
        UnloadRenderTexture(renderTarget);
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

int main()
{
    Squareball::Main();
}
