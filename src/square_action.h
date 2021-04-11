#ifndef SQUARE_ACTION_H_
#define SQUARE_ACTION_H_

#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"
#include "utility.h"


void inn(Player *player);

void shop(Player *player, int item);

void hot_spring(Player *player, int hotSpringTk);

void temple(Player *player);

void farm(Player *player);

void encounter(Player *player, int choices);

void pano_ric(Player *player);

void pano_mon(Player *player);

void pano_sea(Player *player);

#endif
