#include "raylib.h"
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TILE_SIZE 20
#define MAP_WIDTH 40
#define MAP_HEIGHT 30

#define MAX_ROOMS 10
#define MIN_ROOM_SIZE 4
#define MAX_ROOM_SIZE 8

typedef enum {
    GAME_PLAYING,
    GAME_WON
} GameState;

typedef struct {
    int x, y;
} Player;

typedef struct {
    int x, y;
} Cell;

typedef struct {
    int x, y, width, height;
} Room;

int map[MAP_HEIGHT][MAP_WIDTH];
Room rooms[MAX_ROOMS];
int roomCount = 0;
Player player;
Cell exitDoor;
GameState gameState = GAME_PLAYING;


void InitializeMap() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            map[y][x] = 1;
        }
    }
}


int Overlaps(Room a, Room b) {
    return !(a.x + a.width < b.x ||
             a.x > b.x + b.width ||
             a.y + a.height < b.y ||
             a.y > b.y + b.height);
}


void AddRoomsToMap() {
    roomCount = 0;
    for (int i = 0; i < MAX_ROOMS; i++) {
        Room newRoom;
        newRoom.width = MIN_ROOM_SIZE + rand() % (MAX_ROOM_SIZE - MIN_ROOM_SIZE + 1);
        newRoom.height = MIN_ROOM_SIZE + rand() % (MAX_ROOM_SIZE - MIN_ROOM_SIZE + 1);
        newRoom.x = 1 + rand() % (MAP_WIDTH - newRoom.width - 1);
        newRoom.y = 1 + rand() % (MAP_HEIGHT - newRoom.height - 1);


        int overlaps = 0;
        for (int j = 0; j < roomCount; j++) {
            if (Overlaps(newRoom, rooms[j])) {
                overlaps = 1;
                break;
            }
        }

        if (!overlaps) {
            rooms[roomCount++] = newRoom;

            for (int y = newRoom.y; y < newRoom.y + newRoom.height; y++) {
                for (int x = newRoom.x; x < newRoom.x + newRoom.width; x++) {
                    map[y][x] = 0;
                }
            }
        }
    }
}

void ConnectRooms(Room a, Room b) {
    int ax = a.x + a.width / 2;
    int ay = a.y + a.height / 2;
    int bx = b.x + b.width / 2;
    int by = b.y + b.height / 2;

    if (rand() % 2) {
        for (int x = (ax < bx ? ax : bx); x <= (ax > bx ? ax : bx); x++) {
            map[ay][x] = 0;
        }
        for (int y = (ay < by ? ay : by); y <= (ay > by ? ay : by); y++) {
            map[y][bx] = 0;
        }
    } else {

        for (int y = (ay < by ? ay : by); y <= (ay > by ? ay : by); y++) {
            map[y][ax] = 0;
        }
        for (int x = (ax < bx ? ax : bx); x <= (ax > bx ? ax : bx); x++) {
            map[by][x] = 0;
        }
    }
}


void GenerateDungeon() {
    InitializeMap();
    AddRoomsToMap();


    for (int i = 1; i < roomCount; i++) {
        ConnectRooms(rooms[i - 1], rooms[i]);
    }
}


void PlacePlayerAtStart() {
    player.x = rooms[0].x + rooms[0].width / 2;
    player.y = rooms[0].y + rooms[0].height / 2;
}

void PlaceExitDoor() {
    Room farthestRoom = rooms[0];
    int maxDistance = 0;

    for (int i = 0; i < roomCount; i++) {
        Room r = rooms[i];
        int dist = (r.x * r.x + r.y * r.y);
        if (dist > maxDistance) {
            maxDistance = dist;
            farthestRoom = r;
        }
    }

    exitDoor.x = farthestRoom.x + farthestRoom.width / 2;
    exitDoor.y = farthestRoom.y + farthestRoom.height / 2;
}

void DrawMap() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            Color color = map[y][x] == 1 ? DARKGRAY : LIGHTGRAY;
            DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, color);
        }
    }

    DrawRectangle(exitDoor.x * TILE_SIZE, exitDoor.y * TILE_SIZE, TILE_SIZE, TILE_SIZE, GREEN);
}

int PlayerAtExit() {
    return player.x == exitDoor.x && player.y == exitDoor.y;
}

void ResetGame() {
    GenerateDungeon();
    PlacePlayerAtStart();
    PlaceExitDoor();
    gameState = GAME_PLAYING;
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dungeon Crawler - Rooms and Corridors");
    SetTargetFPS(60);
    srand(time(NULL));

    ResetGame();

    while (!WindowShouldClose()) {
        if (gameState == GAME_PLAYING) {
            if (IsKeyDown(KEY_W) && map[player.y - 1][player.x] == 0) player.y--;
            if (IsKeyDown(KEY_S) && map[player.y + 1][player.x] == 0) player.y++;
            if (IsKeyDown(KEY_A) && map[player.y][player.x - 1] == 0) player.x--;
            if (IsKeyDown(KEY_D) && map[player.y][player.x + 1] == 0) player.x++;

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
            DrawRectangle(player.x * TILE_SIZE, player.y * TILE_SIZE, TILE_SIZE, TILE_SIZE, RED);
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
