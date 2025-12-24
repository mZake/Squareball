#pragma once

#include <SDL3/SDL.h>

namespace Squareball
{
    struct PrototypeScene
    {
        float player_x;
        float player_y;
    };
    
    void UpdatePrototypeScene(PrototypeScene& scene, float delta_time);
    void RenderPrototypeScene(PrototypeScene& scene, SDL_Renderer* renderer);
    
    namespace SceneManager
    {
        void Update(float delta_time);
        void Render(SDL_Renderer* renderer);
    }
}
