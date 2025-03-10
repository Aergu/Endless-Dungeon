//
// Created by media on 3/10/2025.
//
#include "Player_settings.h"
#include "Dungeon_settings.h"
#include

void PlacePlayerAtStart() {
    player.x = rooms[0].x + rooms[0].width / 2;
    player.y = rooms[0].y + rooms[0].height / 2;
}