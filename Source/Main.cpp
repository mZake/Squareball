#include <raylib.h>
#include <raymath.h>

struct Player
{
    Vector2     position;
    Vector2     direction;
    float       speed;
};

static void UpdatePlayer(Player& player)
{
    float delta = GetFrameTime();

    player.direction.x = (int)IsKeyDown(KEY_D) - (int)IsKeyDown(KEY_A);
    player.direction.y = (int)IsKeyDown(KEY_S) - (int)IsKeyDown(KEY_W);
    player.direction = Vector2Normalize(player.direction);

    player.position += player.direction * player.speed * delta;
}

static void DrawPlayer(Player& player)
{
    DrawRectangleV(player.position, Vector2{ 64, 64 }, WHITE);
}

int main()
{
    InitWindow(1152, 648, "Squareball");

    Player player = {};
    player.speed = 300.0f;

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLUE);

        UpdatePlayer(player);
        DrawPlayer(player);
        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();
}
