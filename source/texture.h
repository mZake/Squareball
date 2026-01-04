#pragma once

#include <SDL3/SDL.h>

#include "core.h"

namespace Squareball
{
    using TextureID = int32;
    
    struct Texture2D
    {
        SDL_Texture* handle;
        int32 width;
        int32 height;
    };
    
    namespace TextureManager
    {
        void Init();
        void Shutdown();
        
        TextureID LoadTexture(SDL_Renderer* renderer, const char* filepath);
        Texture2D GetTextureFromID(TextureID id);
    }
}
