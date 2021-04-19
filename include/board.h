#ifndef BOARD_H_
#define BOARD_H_

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <utility.h>
#include <account.h>
#include <game.h>
#include <square_draw.h>
#include <square_action.h>

typedef struct
{
	Camera camera;
	SquareGui* squareGui;

	Player players[BOARD_PLAYERS];		// Liste des joueurs
	int playerCount;									// nb de joueurs sur le plateau

	Square squares[BOARD_SQUARES];
	int squareCount;

	int innFoods[6];
	int innFoodCount;

	int turn;													// Index du joueur qui joue ce tour
} Board;

extern Board board;

void load_squares(Square *squares, int playerCount);

Board load_board(const char* path);
void save_board(Board board, const char* path);

void init_board(Account* loggedAccount);

void hover_board(SDL_Point* mousePos);
void click_board(SDL_Point* mousePos);

int whos_turn_is_it(void);
void random_move(void);

void draw_bg(void);
void draw_board(void);
void draw_squares(Board* board);
void draw_hud(void);

void square_action(Square* square);

#endif
