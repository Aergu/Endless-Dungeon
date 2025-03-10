#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include "Player_settings.h"
#include "Dungeon_settings.h"


int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dungeon Crawler ver 0.1");
    SetTargetFPS(60);
    srand(time(NULL));
    ResetGame();


    while (!WindowShouldClose()) {
        if (gameState == GAME_PLAYING) {
            if (IsKeyDown(KEY_W) && map[player.y - PLAYER_SPEED][player.x] == 0)
            {
                player.offset_y--;
                if (player.offset_y <= -(TILE_SIZE / 2)) {
                    player.y--;
                    player.offset_y *= -1;
                }
            }
            if (IsKeyDown(KEY_S) && map[player.y + PLAYER_SPEED][player.x] == 0)
            {
                player.offset_y++;
                if (player.offset_y >= (TILE_SIZE / 2)) {
                    player.y++;
                    player.offset_y *= -1;
                }
            }
            if (IsKeyDown(KEY_A) && map[player.y][player.x - PLAYER_SPEED] == 0)
            {
                player.offset_x--;
                if (player.offset_x <= -(TILE_SIZE / 2)) {
                    player.x--;
                    player.offset_x *= -1;
                }
            }
            if (IsKeyDown(KEY_D) && map[player.y][player.x + PLAYER_SPEED] == 0) {
                player.offset_x++;
                if (player.offset_x >= (TILE_SIZE / 2)) {
                    player.x++;
                    player.offset_x *= -1;
                }
            }

            if (PlayerAtExit()) {
                gameState = GAME_WON;
            }

            if (IsKeyPressed(KEY_SPACE)) {
                ResetGame();
            }
        } else if (gameState == GAME_WON) {
            if (IsKeyPressed(KEY_SPACE)) {
                ResetGame();
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (gameState == GAME_PLAYING) {
            DrawMap();
            DrawRectangle((player.x * TILE_SIZE) + player.offset_x,
                (player.y * TILE_SIZE) + player.offset_y,
                TILE_SIZE,
                TILE_SIZE, RED);
            DrawRectangleLinesEx((Rectangle){player.x * TILE_SIZE, player.y * TILE_SIZE, TILE_SIZE, TILE_SIZE}, 1, YELLOW);
            DrawText("Press SPACE to regenerate the dungeon", 10, 10, 20, BLACK);
        } else if (gameState == GAME_WON) {
            DrawText("YOU WIN!", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 20, 40, GREEN);
            DrawText("Press SPACE to play again", SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2 + 20, 20, DARKGRAY);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
