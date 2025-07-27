#include "Match.h"

#include <raylib.h>
#include <raymath.h>

#include <vector>

#include "Collision.h"
#include "Entity.h"
#include "Game.h"
#include "Tilemap.h"

namespace Squareball
{
    static void OnMatchUpdate(float delta);
    static void OnMatchRender();
    
    static void UpdateEntities(float delta);
    static void MoveEntitiesX();
    static void MoveEntitiesY();
    static void ProcessCollisions();
    static void DrawEntities();
    
    static void CustomDrawFPS();

    struct Match
    {
        int     PlayerCount;
        Player  Players[4];
        Ball    Ball;
        Tilemap Map;
    };

    static Match s_Match = {};

    static std::vector<Tile> s_TestTiles = {
        { { 0.0f,   0.0f }, TileFlags_None },
        { { 64.0f,  0.0f }, TileFlags_None },
        { { 128.0f, 0.0f }, TileFlags_None },
        { { 192.0f, 0.0f }, TileFlags_None },
        { { 0.0f,   64.0f }, TileFlags_None },
        { { 64.0f,  64.0f }, TileFlags_None },
        { { 128.0f, 64.0f }, TileFlags_None },
        { { 192.0f, 64.0f }, TileFlags_None },
        { { 0.0f,   128.0f }, TileFlags_None },
        { { 64.0f,  128.0f }, TileFlags_None },
        { { 128.0f, 128.0f }, TileFlags_None },
        { { 192.0f, 128.0f }, TileFlags_None },

        { { 0.0f,   192.0f }, TileFlags_Wall },
        { { 64.0f,  192.0f }, TileFlags_Wall },
        { { 128.0f, 192.0f }, TileFlags_Wall },
        { { 192.0f, 192.0f }, TileFlags_Wall },
        { { 0.0f,   256.0f }, TileFlags_Wall },
        { { 64.0f,  256.0f }, TileFlags_Wall },
        { { 128.0f, 256.0f }, TileFlags_Wall },
        { { 192.0f, 256.0f }, TileFlags_Wall },
    };

    static std::vector<int> s_TestMap = {
        14, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 15,
        16, 0 , 1,  0 , 1,  0 , 1,  0 , 1,  0 , 1,  0 , 1,  0 , 1,  0 , 3 , 17,
        16, 4 , 5,  4 , 5,  4 , 5,  4 , 5,  4 , 5,  4 , 5,  4 , 5,  4 , 7 , 17,
        16, 4 , 5,  4 , 5,  4 , 5,  4 , 5,  4 , 5,  4 , 5,  4 , 5,  4 , 7 , 17,
        16, 4 , 5,  4 , 5,  4 , 5,  4 , 5,  4 , 5,  4 , 5,  4 , 5,  4 , 7 , 17,
        16, 4 , 5,  4 , 5,  4 , 5,  4 , 5,  4 , 5,  4 , 5,  4 , 5,  4 , 7 , 17,
        16, 4 , 5,  4 , 5,  4 , 5,  4 , 5,  4 , 5,  4 , 5,  4 , 5,  4 , 7 , 17,
        16, 4 , 5,  4 , 5,  4 , 5,  4 , 5,  4 , 5,  4 , 5,  4 , 5,  4 , 7 , 17,
        16, 8 , 9,  8 , 9,  8 , 9,  8 , 9,  8 , 9,  8 , 9,  8 , 9,  8 , 11, 17,
        18, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 19,
    };

    void InitMatchScene()
    {
        SetGameUpdateCallback(OnMatchUpdate);
        SetGameRenderCallback(OnMatchRender);

        s_Match.PlayerCount = 2;
        
        s_Match.Players[0].Position = { 64.0f, 64.0f };
        s_Match.Players[0].Texture = LoadTexture("Resources/Player1.png");
        s_Match.Players[0].Width = 64;
        s_Match.Players[0].Height = 64;
        s_Match.Players[0].Controller = PlayerController::WASDKeys;
        s_Match.Players[0].Speed = 300.0f;

        s_Match.Players[1].Position = { 300.0f, 300.0f };
        s_Match.Players[1].Texture = LoadTexture("Resources/Player2.png");
        s_Match.Players[1].Width = 64;
        s_Match.Players[1].Height = 64;
        s_Match.Players[1].Controller = PlayerController::None;
        s_Match.Players[1].Speed = 300.0f;

        s_Match.Ball.Position = { 544.0f, 288.0f };
        s_Match.Ball.Texture = LoadTexture("Resources/Ball.png");
        s_Match.Ball.Width = 48;
        s_Match.Ball.Height = 48;
        s_Match.Ball.Friction = 0.2f;
        s_Match.Ball.ImpulseForce = 4.0f;

        s_Match.Map.Width = 18;
        s_Match.Map.Height = 10;
        s_Match.Map.Tileset.TileWidth = 64;
        s_Match.Map.Tileset.TileHeight = 64;
        s_Match.Map.Tileset.Atlas = LoadTexture("Resources/TestAtlas.png");
        s_Match.Map.Tileset.Tiles = std::move(s_TestTiles);
        s_Match.Map.Tiles = std::move(s_TestMap);
    }

    static void OnMatchUpdate(float delta)
    {
        UpdateEntities(delta);
        
        MoveEntitiesX();
        ProcessCollisions();

        MoveEntitiesY();
        ProcessCollisions();
    }

    static void OnMatchRender()
    {
        ClearBackground(GREEN);
        DrawTilemap(s_Match.Map);
        DrawEntities();
        CustomDrawFPS();
    }

    static void UpdateEntities(float delta)
    {
        for (int i = 0; i < s_Match.PlayerCount; i++)
            UpdatePlayer(s_Match.Players[i], delta);
        
        UpdateBall(s_Match.Ball, delta);
    }

    static void MoveEntitiesX()
    {
        for (int i = 0; i < s_Match.PlayerCount; i++)
            MoveEntityX(s_Match.Players[i]);
        
        MoveEntityX(s_Match.Ball);
    }

    static void MoveEntitiesY()
    {
        for (int i = 0; i < s_Match.PlayerCount; i++)
            MoveEntityY(s_Match.Players[i]);
        
        MoveEntityY(s_Match.Ball);
    }

    static void ProcessCollisions()
    {
        for (int i = 0; i < s_Match.PlayerCount; i++)
            ProcessCollisionPlayerTilemap(s_Match.Players[i], s_Match.Map);
        
        ProcessCollisionBallTilemap(s_Match.Ball, s_Match.Map);
        
        for (int i = 0; i < s_Match.PlayerCount - 1; i++)
            for (int j = i + 1; j < s_Match.PlayerCount; j++)
                ProcessCollisionPlayers(s_Match.Players[i], s_Match.Players[j]);

        for (int i = 0; i < s_Match.PlayerCount; i++)
            ProcessCollisionPlayerBall(s_Match.Players[i], s_Match.Ball);
    }

    static void DrawEntities()
    {
        for (int i = 0; i < s_Match.PlayerCount; i++)
            DrawEntity(s_Match.Players[i]);
        
        DrawEntity(s_Match.Ball);
    }

    static void CustomDrawFPS()
    {
        int fps = GetFPS();
        const char* text = TextFormat("FPS: %d", fps);
        DrawText(text, 10, 10, 30, BLACK);
    }
}
