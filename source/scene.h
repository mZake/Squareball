#pragma once

#include <SDL3/SDL.h>

#include "texture.h"
#include "tilemap.h"

namespace Squareball
{
    struct PrototypeScene
    {
        TextureID player_texture_id;
        Tilemap tilemap;
        float player_x;
        float player_y;
    };
    
    void InitPrototypeScene(PrototypeScene& scene, SDL_Renderer* renderer);
    void UpdatePrototypeScene(PrototypeScene& scene, float delta_time);
    void RenderPrototypeScene(PrototypeScene& scene, SDL_Renderer* renderer);
    
    namespace SceneManager
    {
        void Init(SDL_Renderer* renderer);
        void Update(float delta_time);
        void Render(SDL_Renderer* renderer);
    }
}
