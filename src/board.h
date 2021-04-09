#ifndef BOARD_H_
#define BOARD_H_

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utility.h"
#include "game.h"
#include "square_action.h"

extern Board board;
extern Ressources ressources;

void load_squares(const char* path, Square *squares);

Board load_board(const char* path);
void save_board(Board board, const char* path);

void init_board(void);

void load_ressources(void);

int whos_turn_is_it(void);
void random_move(void);

void draw_bg(void);
void draw_board(void);
void draw_squares(int squareCount, Square squares[]);

void draw_test(void);

#endif
