#include <SDL3/SDL.h>

#include "scene.h"

namespace Squareball
{
    void UpdatePrototypeScene(PrototypeScene& scene, float delta_time)
    {
        const bool* keyboard = SDL_GetKeyboardState(nullptr);
        bool w_pressed = keyboard[SDL_SCANCODE_W];
        bool a_pressed = keyboard[SDL_SCANCODE_A];
        bool s_pressed = keyboard[SDL_SCANCODE_S];
        bool d_pressed = keyboard[SDL_SCANCODE_D];
        
        float dir_x, dir_y;
        if (w_pressed)
            dir_y += -1.0f;
        if (a_pressed)
            dir_x += -1.0f;
        if (s_pressed)
            dir_y += 1.0f;
        if (d_pressed)
            dir_x += 1.0f;
        
        scene.player_x += dir_x * 100 * delta_time;
        scene.player_y += dir_y * 100 * delta_time;
    }
    
    void RenderPrototypeScene(PrototypeScene& scene, SDL_Renderer* renderer)
    {
        SDL_FRect dest_rect;
        dest_rect.x = scene.player_x;
        dest_rect.y = scene.player_y;
        dest_rect.w = 32;
        dest_rect.h = 32;
        
        SDL_SetRenderDrawColor(renderer, 80, 160, 80, 255);
        SDL_RenderFillRect(renderer, &dest_rect);
    }
}

namespace Squareball::SceneManager
{
    static PrototypeScene s_Scene = {};
    
    void Update(float delta_time)
    {
        UpdatePrototypeScene(s_Scene, delta_time);
    }
    
    void Render(SDL_Renderer* renderer)
    {
        RenderPrototypeScene(s_Scene, renderer);
    }
}
