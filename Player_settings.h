//
// Created by media on 3/10/2025.
//


#ifndef PLAYER_SETTINGS_H
#define PLAYER_SETTINGS_H
#define PLAYER_SPEED 2

#include "Dungeon_settings.h"



int PlayerAtExit() {
    return player.x == exitDoor.x && player.y == exitDoor.y;
}


void InitializeMap();

#endif //PLAYER_SETTINGS_H
