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

typedef enum
{
	GP_INIT,
	GP_WAIT_LOCAL,
	GP_WAIT_LAN,
	GP_COOLDOWN,
	GP_GAME_OVER
} GamePhase;

typedef struct
{
	Camera camera;

	Player players[BOARD_PLAYERS];
	int playerCount;

	Square squares[BOARD_SQUARES];
	int squareCount;

	GamePhase phase;
	BoardMode mode;

	SquareId squareId;
	SquareGui sgui;
} Board;

extern Board board;

void load_squares(Square *squares, int playerCount);

Board load_board(const char* path);
void save_board(Board board, const char* path);

void init_board(Account* loggedAccount, TextureMgr* textureMgr);

void board_update();
void board_event(SDL_Event* event, SDL_Point* mousePos);
void board_mouse(SDL_Point* mousePos, SDL_bool click);

int whos_turn_is_it(void);
void random_move(void);

void update_player_ai(Player* player);
void camera_ai(AnchorInfo* ai, Camera camera);
void camera_draw_sprite(Sprite* sprite, Camera camera);

void draw_bg(void);
void draw_board(void);
void draw_squares(Board* board);
void draw_hud(Hud* hud);

void square_action(Square* square);

#endif
