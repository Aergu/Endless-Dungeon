#include "raylib.h"
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TILE_SIZE 20
#define MAP_WIDTH 40
#define MAP_HEIGHT 30

typedef struct {
    int x, y;
} Player;

int map[MAP_HEIGHT][MAP_WIDTH];

void InitializeMap() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            map[y][x] = 1;  // 1 is a wall
        }
    }

    for (int x = 1; x < MAP_WIDTH - 1; x++) {
        map[MAP_HEIGHT / 2][x] = 0;  // 0 is a path
    }
}

void DrawMap() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            Color color = map[y][x] == 1 ? DARKGRAY : LIGHTGRAY;
            DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, color);
        }
    }
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dungeon Crawler with Raylib");
    SetTargetFPS(60);

    Player player = {1, MAP_HEIGHT / 2};
    InitializeMap();

    while (!WindowShouldClose()) {

        if (IsKeyDown(KEY_W) && map[player.y - 1][player.x] == 0) player.y--;
        if (IsKeyDown(KEY_S) && map[player.y + 1][player.x] == 0) player.y++;
        if (IsKeyDown(KEY_A) && map[player.y][player.x - 1] == 0) player.x--;
        if (IsKeyDown(KEY_D) && map[player.y][player.x + 1] == 0) player.x++;


        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawMap();
        DrawRectangle(player.x * TILE_SIZE, player.y * TILE_SIZE, TILE_SIZE, TILE_SIZE, RED);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
