#include "Match.h"

#include "Core/Collision.h"
#include "Core/Entity.h"
#include "Core/Tilemap.h"
#include "Core/Tileset.h"

#include <raylib.h>
#include <raymath.h>

#include <vector>

namespace Squareball
{
    enum class PlayerController
    {
        None = 0,
        Arrows,
        WASD,
    };
    
    struct Player : public Entity
    {
        PlayerController Controller;
        float MoveSpeed;
    };
    
    struct Ball : public Entity
    {
        float Friction;
        float Impulse;
    };
    
    struct World
    {
        Tileset MapTileset;
        Tilemap MapTilemap;
        Player Players[4];
        Ball Ball;
        int PlayerCount;
    };
    
    static World s_World = {};
    
    void UpdatePlayer(Player& player, float deltaTime);
    void UpdateBall(Ball& ball, float deltaTime);
    
    void ProcessCollisionPlayers(Player& player1, Player& player2);
    void ProcessCollisionPlayerBall(Player& player, Ball& ball);
    void ProcessCollisionPlayerTilemap(Player& player, const Tilemap& map);
    void ProcessCollisionBallTilemap(Ball& ball, const Tilemap& map);
    
    void UpdateWorldEntities(float deltaTime);
    void MoveWorldEntitiesX();
    void MoveWorldEntitiesY();
    void ProcessWorldCollisions();
    void DrawWorldComponents();
    
    void CustomDrawFPS();
    
    void OnMatchInit()
    {
        s_World.PlayerCount = 2;
        
        s_World.Players[0].Position = { 64.0f, 64.0f };
        s_World.Players[0].Texture = LoadTexture("Resources/Player1.png");
        s_World.Players[0].Width = 64;
        s_World.Players[0].Height = 64;
        s_World.Players[0].Controller = PlayerController::WASD;
        s_World.Players[0].MoveSpeed = 300.0f;
        
        s_World.Players[1].Position = { 300.0f, 300.0f };
        s_World.Players[1].Texture = LoadTexture("Resources/Player2.png");
        s_World.Players[1].Width = 64;
        s_World.Players[1].Height = 64;
        s_World.Players[1].Controller = PlayerController::Arrows;
        s_World.Players[1].MoveSpeed = 300.0f;
        
        s_World.Ball.Position = { 544.0f, 288.0f };
        s_World.Ball.Texture = LoadTexture("Resources/Ball.png");
        s_World.Ball.Width = 48;
        s_World.Ball.Height = 48;
        s_World.Ball.Friction = 0.2f;
        s_World.Ball.Impulse = 4.0f;
        
        s_World.MapTileset = LoadTileset("Resources/TestTileset.mts");
        s_World.MapTilemap = LoadTilemap("Resources/TestTilemap.mtm", s_World.MapTileset);
    }
    
    void OnMatchUpdate()
    {
        float deltaTime = GetFrameTime();
        
        UpdateWorldEntities(deltaTime);
        
        MoveWorldEntitiesX();
        ProcessWorldCollisions();
        
        MoveWorldEntitiesY();
        ProcessWorldCollisions();
    }
    
    void OnMatchRender()
    {
        ClearBackground(GREEN);
        DrawTilemap(s_World.MapTilemap);
        DrawWorldComponents();
        CustomDrawFPS();
    }
    
    void UpdatePlayer(Player& player, float deltaTime)
    {
        Vector2 direction = {};
        
        if (player.Controller == PlayerController::WASD)
        {
            direction.x = (int)IsKeyDown(KEY_D) - (int)IsKeyDown(KEY_A);
            direction.y = (int)IsKeyDown(KEY_S) - (int)IsKeyDown(KEY_W);
        }
        else if (player.Controller == PlayerController::Arrows)
        {
            direction.x = (int)IsKeyDown(KEY_RIGHT) - (int)IsKeyDown(KEY_LEFT);
            direction.y = (int)IsKeyDown(KEY_DOWN) - (int)IsKeyDown(KEY_UP);
        }
        
        if (direction != Vector2Zero())
            direction = Vector2Normalize(direction);
        
        player.Velocity = direction * player.MoveSpeed * deltaTime;
    }
    
    void UpdateBall(Ball& ball, float deltaTime)
    {
        if (ball.Velocity != Vector2Zero())
            ball.Velocity -= ball.Velocity * ball.Friction * deltaTime;
    }
    
    void ProcessCollisionPlayers(Player& player1, Player& player2)
    {
        Intersection intersection = IntersectEntities(player1, player2);
        if (intersection.Overlapping)
        {
            player1.Position -= intersection.Normal * intersection.Depth / 2;
            player2.Position += intersection.Normal * intersection.Depth / 2;
        }
    }
    
    void ProcessCollisionPlayerBall(Player& player, Ball& ball)
    {
        Intersection intersection = IntersectEntities(player, ball);
        if (intersection.Overlapping)
        {
            player.Position -= intersection.Normal * intersection.Depth;
            ball.Velocity += intersection.Normal * ball.Impulse;
        }
    }
    
    void ProcessCollisionPlayerTilemap(Player& player, const Tilemap& map)
    {
        Intersection intersection = IntersectEntityTilemap(player, map);
        if (intersection.Overlapping)
            player.Position -= intersection.Normal * intersection.Depth;
    }
    
    void ProcessCollisionBallTilemap(Ball& ball, const Tilemap& map)
    {
        Intersection intersection = IntersectEntityTilemap(ball, map);
        if (intersection.Overlapping)
        {
            ball.Position -= intersection.Normal * intersection.Depth;
            
            if (intersection.Normal.x != 0.0f)
                ball.Velocity.x *= -1;
            else if (intersection.Normal.y != 0.0f)
                ball.Velocity.y *= -1;
        }
    }
    
    void UpdateWorldEntities(float deltaTime)
    {
        for (int i = 0; i < s_World.PlayerCount; i++)
            UpdatePlayer(s_World.Players[i], deltaTime);
        
        UpdateBall(s_World.Ball, deltaTime);
    }
    
    void MoveWorldEntitiesX()
    {
        for (int i = 0; i < s_World.PlayerCount; i++)
            MoveEntityX(s_World.Players[i]);
        
        MoveEntityX(s_World.Ball);
    }
    
    void MoveWorldEntitiesY()
    {
        for (int i = 0; i < s_World.PlayerCount; i++)
            MoveEntityY(s_World.Players[i]);
        
        MoveEntityY(s_World.Ball);
    }
    
    void ProcessWorldCollisions()
    {
        for (int i = 0; i < s_World.PlayerCount; i++)
            ProcessCollisionPlayerTilemap(s_World.Players[i], s_World.MapTilemap);
        
        ProcessCollisionBallTilemap(s_World.Ball, s_World.MapTilemap);
        
        for (int i = 0; i < s_World.PlayerCount - 1; i++)
            for (int j = i + 1; j < s_World.PlayerCount; j++)
                ProcessCollisionPlayers(s_World.Players[i], s_World.Players[j]);
        
        for (int i = 0; i < s_World.PlayerCount; i++)
            ProcessCollisionPlayerBall(s_World.Players[i], s_World.Ball);
    }
    
    void DrawWorldComponents()
    {
        for (int i = 0; i < s_World.PlayerCount; i++)
            DrawEntity(s_World.Players[i]);
        
        DrawEntity(s_World.Ball);
    }
    
    void CustomDrawFPS()
    {
        int fps = GetFPS();
        const char* text = TextFormat("FPS: %d", fps);
        DrawText(text, 10, 10, 30, BLACK);
    }
}
