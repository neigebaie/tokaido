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
	BM_INVENTORY,
	BM_SQUARE,
	BM_ACHIEVEMENTS,
	BM_GAMEOVER
} BoardMode;

typedef struct
{
	Camera camera;

	SDL_bool started;
	SDL_bool initialized;

	Player players[BOARD_PLAYERS];
	int playerCount;

	Square squares[BOARD_SQUARES];
	int squareCount;

	BoardMode mode;

	SquareId squareId;
	SquareGui* sgui; // Gui de la case
	SDL_bool specialGui; // Gui custom pour les capacités de personnages

	int lastInnPos; // position du dernier relai
	Food* innFoods[6]; // repas du relai actuel

	double waitUntil; // délai entre les tours ou pour les animations
	Player* playing; // joueur en train de jouer
	Recap recap; // récapitulatif des actions d'un joueur lors de son tour (pour les bots)

	Hud* hud; // barre d'état en haut de l'écran
	SDL_bool drawLboard; // booléen pour l'affichage du leaderboard
	Lboard* lboard;

	AchievementsGui* achievementsGui;
	Menu* gameOverMenu;
} Board;

extern Board board;

// initialise les cases sur le plateau
void load_squares(Square *squares, int playerCount);

// chargement/sauvegarde du plateau
Board load_board(const char* path);
void save_board(Board board, const char* path);

void init_board(Account* loggedAccount, TextureMgr* textureMgr);
SDL_bool is_game_started(); // getter pour board.started

void board_update();
// pour les event (souris, clavier, etc)
void board_event(SDL_Event* event, SDL_Point* mousePos, MenuId* menuId);
void board_mouse(SDL_Point* mousePos, SDL_bool click, MenuId* menuId);


int whos_turn_is_it(); // retourne l'id du joueur qui doit jouer
int highlight_possible_moves(Player player); // met en surbrillance les cases possibles
SDL_bool is_move_allowed(int position, Player player);


void update_player_ai(Player* player); // met à jour la position en pixel par rapport à la position sur le plateau
void camera_ai(AnchorInfo* ai, Camera camera); // transforme les coords absolues en coors relatives à la camera
void camera_draw_sprite(Sprite* sprite, Camera camera); // affiche un sprite relativement à la camera

void draw_bg(); // affiche l'arrière plan
void draw_board();
void draw_squares(); // affiches les cases du plateau

void random_move(); // mouvement des pnj
void move_player(Square* square);

void begin_turn();
void end_turn();
void square_action(Square* square); // action des cases (auto pour les bots)

#endif
