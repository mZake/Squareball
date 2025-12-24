#include <stdint.h>
#include <stdlib.h>

#include <SDL3/SDL.h>

#include "app.h"

namespace Squareball::App
{
    static SDL_Window* s_Window = nullptr;
    static SDL_Renderer* s_Renderer = nullptr;
    static bool s_Running = false;
    static uint64_t s_LastTicks = 0;
    
    static float GetDeltaTime()
    {
        uint64_t current_ticks = SDL_GetTicks();
        float delta_time = (current_ticks - s_LastTicks) / 1000.0f;
        s_LastTicks = current_ticks;
        
        return delta_time;
    }
    
    static void ProcessEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                s_Running = false;
        }
    }
    
    void Init()
    {
        if (!SDL_Init(SDL_INIT_VIDEO))
        {
            SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
            exit(EXIT_FAILURE);
        }
        
        int screen_width = 800;
        int screen_height = 600;
        char window_title[] = "Squareball";
        
        s_Window = SDL_CreateWindow(window_title, screen_width, screen_height, 0);
        if (!s_Window)
        {
            SDL_Log("Failed to create a window: %s", SDL_GetError());
            exit(EXIT_FAILURE);
        }
        
        s_Renderer = SDL_CreateRenderer(s_Window, nullptr);
        if (!s_Renderer)
        {
            SDL_Log("Failed to create a renderer: %s", SDL_GetError());
            exit(EXIT_FAILURE);
        }
        
        s_Running = true;
    }
    
    void Shutdown()
    {
        if (s_Window)
            SDL_DestroyWindow(s_Window);
        
        if (s_Renderer)
            SDL_DestroyRenderer(s_Renderer);
        
        s_Window = nullptr;
        s_Renderer = nullptr;
        s_Running = false;
    }
    
    void MainLoop()
    {
        float red = 0.0f;
        float green = 0.0f;
        float blue = 0.0f;
        
        s_LastTicks = SDL_GetTicks();
        
        while (s_Running)
        {
            float delta_time = GetDeltaTime();
            
            ProcessEvents();
            
            red += 1.0f * delta_time;
            green += 2.0f * delta_time;
            blue += 3.0f * delta_time;
            
            SDL_SetRenderDrawColor(s_Renderer, red, green, blue, 255);
            SDL_RenderClear(s_Renderer);
            SDL_RenderPresent(s_Renderer);
        }
    }
}
