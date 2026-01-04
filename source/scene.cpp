#include <SDL3/SDL.h>

#include "scene.h"
#include "texture.h"
#include "tilemap.h"

namespace Squareball
{
    void InitPrototypeScene(PrototypeScene& scene, SDL_Renderer* renderer)
    {
        scene.player_texture_id = TextureManager::LoadTexture(renderer, "resources/player1.png");
        
        TextureID atlas_id = TextureManager::LoadTexture(renderer, "resources/test_atlas.png");
        int32 tile_width = 64;
        int32 tile_height = 64;
        Tileset tileset = CreateTileset(atlas_id, tile_width, tile_height);
        Tilemap tilemap = LoadTilemap(tileset, "resources/test_tilemap.sbm");
        
        scene.tilemap = tilemap;
        
        scene.player_x = 0.0f;
        scene.player_y = 0.0f;
    }
    
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
        DrawTilemap(renderer, scene.tilemap);
        
        SDL_FRect dest_rect;
        dest_rect.x = scene.player_x;
        dest_rect.y = scene.player_y;
        dest_rect.w = 64;
        dest_rect.h = 64;
        
        Texture2D player_texture = TextureManager::GetTextureFromID(scene.player_texture_id);
        
        SDL_RenderTexture(renderer, player_texture.handle, nullptr, &dest_rect);
    }
}

namespace Squareball::SceneManager
{
    static PrototypeScene s_Scene = {};
    
    void Init(SDL_Renderer* renderer)
    {
        InitPrototypeScene(s_Scene, renderer);
    }
    
    void Update(float delta_time)
    {
        UpdatePrototypeScene(s_Scene, delta_time);
    }
    
    void Render(SDL_Renderer* renderer)
    {
        RenderPrototypeScene(s_Scene, renderer);
    }
}
