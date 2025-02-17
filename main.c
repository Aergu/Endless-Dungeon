#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 20
#define HEIGHT 10
#define ROOM_COUNT 5
#define TILE_SIZE 40

char dungeon[HEIGHT][WIDTH];


void initDungeon() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            dungeon[y][x] = '#';
        }
    }
}


void createRooms() {
    for (int i = 0; i < ROOM_COUNT; i++) {
        int w = 3 + rand() % 4;
        int h = 3 + rand() % 4;
        int x = rand() % (WIDTH - w - 1);
        int y = rand() % (HEIGHT - h - 1);

        for (int dy = 0; dy < h; dy++) {
            for (int dx = 0; dx < w; dx++) {
                dungeon[y + dy][x + dx] = '.';  // Floor
            }
        }
    }
}


void drawDungeon() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            Color tileColor = (dungeon[y][x] == '#') ? DARKGRAY : LIGHTGRAY;
            DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, tileColor);
        }
    }
}

int main() {
    srand(time(NULL));

    initDungeon();
    createRooms();

    InitWindow(WIDTH * TILE_SIZE, HEIGHT * TILE_SIZE, "Procedural Dungeon");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        drawDungeon();  

        EndDrawing();
    }

    CloseWindow();
    return 0;
}