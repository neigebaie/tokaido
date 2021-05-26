#ifndef SQUARE_DRAW_H_
#define SQUARE_DRAW_H_

#include <stdio.h>

#include <game.h>
#include <gui.h>

#define INN_FRAMES 6
#define SHOP_FRAMES 3

#define PAN_RICE_CARDS 3
#define PAN_MOUNT_CARDS 4
#define PAN_SEA_CARDS 5

typedef int (*compfn)(const void*, const void*);

// définie si un cadre contient un repas ou un souvenir
typedef enum
{
	CONTENT_FOOD,
	CONTENT_ITEM
} ContentType;

// contenu du cadre
typedef union {
	Food food;
	Item item;
} Content;

// cadre utilisé dans l'échoppe et le relai
typedef struct
{
	AnchorInfo ai;
	Text* title;
	Sprite bg;

	State state;
	SDL_bool sold;

	Sprite coinIcon;
	Text* coinText;

	Sprite bundleTkIcon;
	Text* bundleTkText;

	Sprite itemCatIcon;

	ContentType contentType;
	Content content;

} Frame;

// typedef struct
// {
// 	Sprite* itemCatIcons[ITEM_CATS];
// 	Text* itemCatTexts[ITEM_CATS];
// } CollectionFrame;


typedef struct
{
	Menu* menu;
	SquareId squareId;

	Frame** frames;
	int frameCount;

	// union {
	// 	CollectionFrame colFrame;
	// 	Sprite* panorama;
	// } special;

} SquareGui;


// barre d'état
typedef struct
{
	Text* nick;
	Sprite travelerIcon;

	Sprite coinIcon;
	Text* coinText;

	Sprite bundleTkIcon;
	Text* bundleTkText;

	Sprite templeCoinIcon;
	Text* templeCoinText;
} Hud;

// leaderboard
typedef struct
{
	Sprite bg;
	Sprite colIcons[9];
	Text* texts[9][5];
	Sprite playerIcons[9][5];

	Player** riceList;      // rizière
	Player** mountList;     // montagne
	Player** seaList;       // mer
	Player** templeList;    // temple
	Player** encounterList; // rencontre
	Player** shopList;      // échoppe
	Player** hotSpringList; // source chaude
	Player** innList;       // pièces au relai
	Player** bundleTkList;  // pts de victoire

} Lboard;

typedef struct
{
	Menu* menu;
	Sprite panAchievements[3];
	Sprite templeAchievements[8];
	Sprite otherAchievements[4][5];
	SDL_bool panWinner[3];
	int nbExAequo[4];
} AchievementsGui;

// SquareGui : initialise les menus de cases

SquareGui* new_inn_gui(Food** foods, int foodCount, Player* player);
SquareGui* new_shop_gui(Item* items[], Player* player);
SquareGui* new_hot_spring_gui();
SquareGui* new_temple_gui();
SquareGui* new_encounter_gui(int encounterId, char* obtained);
SquareGui* new_farm_gui();
SquareGui* new_pan_rice_gui(int nb);
SquareGui* new_pan_mount_gui(int nb);
SquareGui* new_pan_sea_gui(int nb);

// Game over
AchievementsGui* new_achievements_gui(Lboard* lboard, Player* players, int playerCount);
void draw_achievements_gui(AchievementsGui* achievementsGui); // affichage du tableau des accomplissements
Menu* new_game_over_gui(Player* players, int playerCount);

// Custom Menu
Menu* new_yoshiyasu_menu(int encounterId1, int encounterId2);
Menu* new_Hiroshige_menu();
Menu* new_Satsuki_menu(int foodId);
Menu* new_Chuubei_menu();
Menu* new_Sasayakko_menu();

// HUD
Hud* new_hud(Player player);
void update_hud(Hud* hud, Player player);
void draw_hud(Hud* hud);
void destroy_hud(Hud* hud);

// COMPARE : utilisé par les qsort du leaderboard
int cmpfunc_rice(const void* a, const void* b);
int cmpfunc_mount(const void* a, const void* b);
int cmpfunc_sea(const void* a, const void* b);
int cmpfunc_temple(const void* a, const void* b);
int cmpfunc_encounter(const void* a, const void* b);
int cmpfunc_shop(const void* a, const void* b);
int cmpfunc_hot_spring(const void* a, const void* b);
int cmpfunc_inn(const void* a, const void* b);
int cmpfunc_bundle_tk(const void* a, const void* b);

// LEADERBOARD
Lboard* new_lboard(Player*  players, int playerCount);
void update_lboard(Lboard* lboard, Player* players, int playerCount);
void draw_lboard(Lboard* lboard);
void destroy_lboard(Lboard* lboard);

// // INVENTORY
// Inventory* new_inv();
// void update_inv(Inventory* inv, Player player);
// void draw_inv(Inventory* inv);
// void destroy_inv(Inventory* inv);

// FRAME
Frame* new_frame(AnchorInfo* ai, ContentType contentType, Content content);
void draw_frame(Frame* frame);

void draw_square_gui(SquareGui* sgui);

#endif
