//
// Created by media on 3/10/2025.
//


#ifndef PLAYER_SETTINGS_H
#define PLAYER_SETTINGS_H
#define PLAYER_SPEED 1

#include "Dungeon_settings.h"


void PlacePlayerAtStart() {
    player.x = rooms[0].x + rooms[0].width / 2;
    player.y = rooms[0].y + rooms[0].height / 2;
}


int PlayerAtExit() {
    return player.x == exitDoor.x && player.y == exitDoor.y;
}


void InitializeMap();

#endif //PLAYER_SETTINGS_H
