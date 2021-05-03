#ifndef SQUARE_ACTION_H_
#define SQUARE_ACTION_H_

#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

#include <game.h>
#include <utility.h>
#include <square_draw.h>

SDL_bool buy_from_frame(Player* player, Frame* frame);

//
// void action_inn(Player *player);
//
// void action_shop(Player *player, int item);
//
void action_hot_spring(Player *player, int hotSpringTk);
//
// void action_temple(Player *player);
//
void action_farm(Player *player);

void action_encounter(Player *player, int id, char* obtained);

void action_pan_rice(Player *player);

void action_pan_mount(Player *player);

void action_pan_sea(Player *player);

#endif
