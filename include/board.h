#ifndef BOARD_H_
#define BOARD_H_

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <utility.h>
#include <account.h>
#include <game.h>
#include <square_init.h>
#include <square_draw.h>
#include <square_action.h>

typedef enum
{
	BM_BOARD,
	BM_LEADER_BOARD,
	BM_INVENTORY,
	BM_SQUARE
} BoardMode;

typedef struct
{
	Camera camera;

	SDL_bool started;

	Player players[BOARD_PLAYERS];
	int playerCount;

	Square squares[BOARD_SQUARES];
	int squareCount;

	BoardMode mode;

	SquareId squareId;
	SquareGui* sgui;
	SDL_bool specialGui;

	int lastInnPos;
	Food* innFoods[6];

	double waitUntil;
	Player* playing;
	Recap recap;

	Hud* hud;
	Lboard* lboard;
} Board;

extern Board board;

void load_squares(Square *squares, int playerCount);

Board load_board(const char* path);
void save_board(Board board, const char* path);

void init_board(Account* loggedAccount, TextureMgr* textureMgr);
SDL_bool is_game_started();

void board_update();
void board_event(SDL_Event* event, SDL_Point* mousePos);
void board_mouse(SDL_Point* mousePos, SDL_bool click);

int whos_turn_is_it();
int highlight_possible_moves(Player player);
SDL_bool is_move_allowed(int position, Player player);


void update_player_ai(Player* player);
void camera_ai(AnchorInfo* ai, Camera camera);
void camera_draw_sprite(Sprite* sprite, Camera camera);

void draw_bg();
void draw_board();
void draw_squares();

void random_move();
void move_player(Square* square);

void begin_turn();
void end_turn();
void square_action(Square* square);

#endif
