#include "Match.h"

#include "Core/Collision.h"
#include "Core/Entity.h"
#include "Core/Tilemap.h"
#include "Core/Tileset.h"

#include <raylib.h>
#include <raymath.h>

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
    
    bool ProcessCollisionPlayerTilemap(Player& player, const Tilemap& map, Axis axis);
    bool ProcessCollisionBallTilemap(Ball& ball, const Tilemap& map, Axis axis);
    bool ProcessCollisionPlayers(Player& player1, Player& player2, Axis axis);
    bool ProcessCollisionPlayerBall(Player& player, Ball& ball, Axis axis);
    
    void UpdateEntities(float deltaTime);
    void DrawEntities();
    
    void UpdateEntitiesPositionX();
    void UpdateEntitiesPositionY();
    void ResolveTilemapCollisionsX();
    void ResolveTilemapCollisionsY();
    void ResolveEntityCollisionsX();
    void ResolveEntityCollisionsY();
    
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
        
        UpdateEntities(deltaTime);
        
        UpdateEntitiesPositionX();
        ResolveTilemapCollisionsX();
        ResolveEntityCollisionsX();
        
        UpdateEntitiesPositionY();
        ResolveTilemapCollisionsY();
        ResolveEntityCollisionsY();
    }
    
    void OnMatchRender()
    {
        ClearBackground(GREEN);
        DrawTilemap(s_World.MapTilemap);
        DrawEntities();
        //CustomDrawFPS();
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
    
    bool ProcessCollisionPlayerTilemap(Player& player, const Tilemap& map, Axis axis)
    {
        Intersection intersection = IntersectEntityTilemap(player, map, axis);
        if (intersection.Overlapping)
        {
            if (axis == Axis::X)
            {
                MoveEntityX(player, -intersection.Normal.x * intersection.Depth);
                player.CanMoveX = false;
            }
            else
            {
                MoveEntityY(player, -intersection.Normal.y * intersection.Depth);
                player.CanMoveY = false;
            }
        }
        
        return intersection.Overlapping;
    }
    
    bool ProcessCollisionBallTilemap(Ball& ball, const Tilemap& map, Axis axis)
    {
        Intersection intersection = IntersectEntityTilemap(ball, map, axis);
        if (intersection.Overlapping)
        {
            if (axis == Axis::X)
            {
                MoveEntityX(ball, -intersection.Normal.x * intersection.Depth);
                ball.Velocity.x *= -1;
            }
            else
            {
                MoveEntityY(ball, -intersection.Normal.y * intersection.Depth);
                ball.Velocity.y *= -1;
            }
        }
        
        return intersection.Overlapping;
    }
    
    bool ProcessCollisionPlayers(Player& player1, Player& player2, Axis axis)
    {
        Intersection intersection = IntersectEntities(player1, player2, axis);
        if (intersection.Overlapping)
        {
            Vector2 correction = intersection.Normal * intersection.Depth / 2;
            Vector2 player1Correction = correction;
            Vector2 player2Correction = correction;
            
            if (axis == Axis::X)
            {
                if (!player1.CanMoveX)
                {
                    player1Correction.x = 0.0f;
                    player2Correction.x *= 2.0f;
                }
                else if (!player2.CanMoveX)
                {
                    player2Correction.x = 0.0f;
                    player1Correction.x *= 2.0f;
                }
                
                MoveEntityX(player1, -player1Correction.x);
                MoveEntityX(player2, player2Correction.x);
            }
            else
            {
                if (!player1.CanMoveY)
                {
                    player1Correction.y = 0.0f;
                    player2Correction.y *= 2.0f;
                }
                else if (!player2.CanMoveY)
                {
                    player2Correction.y = 0.0f;
                    player1Correction.y *= 2.0f;
                }
                
                MoveEntityY(player1, -player1Correction.y);
                MoveEntityY(player2, player2Correction.y);
            }
        }
        
        return intersection.Overlapping;
    }
    
    bool ProcessCollisionPlayerBall(Player& player, Ball& ball, Axis axis)
    {
        Intersection intersection = IntersectEntities(player, ball, axis);
        if (intersection.Overlapping)
        {
            Vector2 correction = intersection.Normal * intersection.Depth;
            
            if (axis == Axis::X)
            {
                if (player.CanMoveX)
                    MoveEntityX(player, -correction.x);
                else
                    MoveEntityX(ball, correction.x);
                
                ball.Velocity.x += intersection.Normal.x * ball.Impulse;
            }
            else
            {
                if (player.CanMoveY)
                    MoveEntityY(player, -correction.y);
                else
                    MoveEntityY(ball, correction.y);
                
                ball.Velocity.y += intersection.Normal.y * ball.Impulse;
            }
        }
        
        return intersection.Overlapping;
    }
    
    void UpdateEntities(float deltaTime)
    {
        for (int i = 0; i < s_World.PlayerCount; i++)
            UpdatePlayer(s_World.Players[i], deltaTime);
        
        UpdateBall(s_World.Ball, deltaTime);
    }
    
    void DrawEntities()
    {
        for (int i = 0; i < s_World.PlayerCount; i++)
            DrawEntity(s_World.Players[i]);
        
        DrawEntity(s_World.Ball);
    }
    
    void UpdateEntitiesPositionX()
    {
        for (int i = 0; i < s_World.PlayerCount; i++)
            UpdateEntityPositionX(s_World.Players[i]);
        
        UpdateEntityPositionX(s_World.Ball);
    }
    
    void UpdateEntitiesPositionY()
    {
        for (int i = 0; i < s_World.PlayerCount; i++)
            UpdateEntityPositionY(s_World.Players[i]);
        
        UpdateEntityPositionY(s_World.Ball);
    }
    
    void ResolveTilemapCollisionsX()
    {
        for (int i = 0; i < s_World.PlayerCount; i++)
        {
            if (s_World.Players[i].MovedX || s_World.Players[i].WasMovingX)
                ProcessCollisionPlayerTilemap(s_World.Players[i], s_World.MapTilemap, Axis::X);
        }
        
        if (s_World.Ball.MovedX || s_World.Ball.WasMovingX)
            ProcessCollisionBallTilemap(s_World.Ball, s_World.MapTilemap, Axis::X);
    }
    
    void ResolveTilemapCollisionsY()
    {
        for (int i = 0; i < s_World.PlayerCount; i++)
        {
            if (s_World.Players[i].MovedY || s_World.Players[i].WasMovingY)
                ProcessCollisionPlayerTilemap(s_World.Players[i], s_World.MapTilemap, Axis::Y);
        }
        
        if (s_World.Ball.MovedY || s_World.Ball.WasMovingY)
            ProcessCollisionBallTilemap(s_World.Ball, s_World.MapTilemap, Axis::Y);
    }
    
    void ResolveEntityCollisionsX()
    {
        constexpr int MaxIterations = 10;
        for (int iter = 0; iter < MaxIterations; iter++)
        {
            bool anyCollision = false;
            
            for (int i = 0; i < s_World.PlayerCount; i++)
            {
                for (int j = i + 1; j < s_World.PlayerCount; j++)
                {
                    if (ProcessCollisionPlayers(s_World.Players[i], s_World.Players[j], Axis::X))
                        anyCollision = true;
                }
                
                if (ProcessCollisionPlayerBall(s_World.Players[i], s_World.Ball, Axis::X))
                    anyCollision = true;
            }
            
            if (!anyCollision)
                break;
        }
    }
    
    void ResolveEntityCollisionsY()
    {
        constexpr int MaxIterations = 10;
        for (int iter = 0; iter < MaxIterations; iter++)
        {
            bool anyCollision = false;
            
            for (int i = 0; i < s_World.PlayerCount; i++)
            {
                for (int j = i + 1; j < s_World.PlayerCount; j++)
                {
                    if (ProcessCollisionPlayers(s_World.Players[i], s_World.Players[j], Axis::Y))
                        anyCollision = true;
                }
                
                if (ProcessCollisionPlayerBall(s_World.Players[i], s_World.Ball, Axis::Y))
                    anyCollision = true;
            }
            
            if (!anyCollision)
                break;
        }
    }
    
    void CustomDrawFPS()
    {
        int fps = GetFPS();
        const char* text = TextFormat("FPS: %d", fps);
        DrawText(text, 10, 10, 30, BLACK);
    }
}
