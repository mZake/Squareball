#include <limits>
#include <vector>

#include <SDL3/SDL.h>
#include <stb_image.h>

#include "core.h"
#include "texture.h"

namespace Squareball::TextureManager
{
    static std::vector<Texture2D> s_Textures;
    
    constexpr size_t TEXTURE_ID_MAX = std::numeric_limits<TextureID>::max();
    
    void Init()
    {
    }
    
    void Shutdown()
    {
        for (const auto& texture : s_Textures)
            SDL_DestroyTexture(texture.handle);
        
        s_Textures.clear();
    }
    
    TextureID LoadTexture(SDL_Renderer* renderer, const char* filepath)
    {
        SDL_assert(renderer != nullptr);
        SDL_assert(filepath != nullptr);
        
        int32 width, height, channels;
        int32 desired_channels = 4;
        
        uint8* pixels = stbi_load(filepath, &width, &height, &channels, desired_channels);
        if (!pixels)
            return -1;
        
        SDL_PixelFormat pixel_format = SDL_PIXELFORMAT_RGBA32;
        int32 pitch = width * desired_channels;
        
        SDL_Surface* surface = SDL_CreateSurfaceFrom(width, height, pixel_format, pixels, pitch);
        if (!surface)
        {
            stbi_image_free(pixels);
            return -1;
        }
        
        SDL_Texture* handle = SDL_CreateTextureFromSurface(renderer, surface);
        if (!handle)
        {
            SDL_DestroySurface(surface);
            stbi_image_free(pixels);
            return -1;
        }
        
        SDL_DestroySurface(surface);
        stbi_image_free(pixels);
        
        size_t texture_array_index = s_Textures.size();
        SDL_assert(texture_array_index <= TEXTURE_ID_MAX);
        TextureID texture_id = static_cast<TextureID>(texture_array_index);
        
        Texture2D texture;
        texture.handle = handle;
        texture.width = width;
        texture.height = height;
        
        s_Textures.push_back(texture);
        
        return texture_id;
    }
    
    Texture2D GetTextureFromID(TextureID id)
    {
        SDL_assert(id >= 0);
        SDL_assert(id < s_Textures.size());
        
        return s_Textures[id];
    }
}
