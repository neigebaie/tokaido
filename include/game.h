#ifndef GAME_H_
#define GAME_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <utility.h>

// camera
#define CAMERA_MIN_ZOOM 0.5
#define CAMERA_MAX_ZOOM 1.25

// ressources
#define SQUARES 10
#define FOODS 14
#define ITEMS 24
#define ITEM_CATS 4
#define ENCOUNTERS 7
#define TRAVELERS 10

// board
#define BOARD_PLAYERS 5
#define BOARD_SQUARES 55

// SQUARE TYPES
#define SQUARE_INN       0
#define SQUARE_SHOP      1
#define SQUARE_HOTSPRING 2
#define SQUARE_TEMPLE    3
#define SQUARE_ENCOUNTER 4
#define SQUARE_FARM      5
#define SQUARE_PAN_RICE  6
#define SQUARE_PAN_MOUNT 7
#define SQUARE_PAN_SEA   8

typedef struct
{
	char name[100];					// nom de la categorie de souvenir
	Sprite* sprite;
	int giveItem;           // Artisan       →  x:quantity
	int givePanCard;        // Guide         →  0:nothing  1:rice  2:mount  3:sea
	int giveBundleTk;       // Samouraï      →  x:quantity
	int giveCoin;           // Noble         →  x:quantity
	int giveTemple;         // Prêtre Shinto →  x:quantity
} Encounter;

typedef struct
{
	char name[100];        // nom de la catégorie
	Sprite* sprite;
} ItemCategory;

typedef struct
{
	char name[100];					// nom du souvenir
	Sprite* sprite;
	int price;
	ItemCategory category;
} Item;

typedef struct
{
	char name[100];        // nom du repas
	Sprite* sprite;
	int price;
} Food;

typedef struct
{
	char name[100];  // nom de la case
	int id;
	Sprite* sprite;
	SDL_Color color;
} SquareType;

typedef struct
{
	char name[100]; // nom de la categorie de souvenir
	Sprite* sprite;
	int startCoins;
} Traveler;

typedef struct
{
	Encounter*		encounters[ENCOUNTERS];  // rencontres
	Food*					foods[FOODS];            // nourritures
	Item*					items[ITEMS];            // souvenirs
	ItemCategory* itemCats[ITEM_CATS];     // catégories
	SquareType*		squareTypes[SQUARES];    // Cases
	Traveler*			travelers[TRAVELERS];    // voyageurs
} Ressources;


typedef struct
{
	Traveler* traveler;     // personnage choisi
	Sprite* nameTag;

	char nickname[100];			// pseudo du joueur si jeu en LAN/WAN
	SDL_bool isHuman;				// joueur IA ou humain

	int position;						// position du joueur sur le plateau
	int roadDist;						// éloignement de la route

	int bundleToken;				// points de victoire accumulés (jeton balûchon)
	int coins;							// pièces possédées
	int templeCoins;				// pièces données au temple
	int hotSpring;					// nombre de passages à une source chaude

	Food* foods[50];
	int   foodCount;

	Item* items[50];
	int   itemCount;

	Encounter* encounters[50];
	int        encounterCount;

	int panRice;						// cartes panorama Rizière
	int panMount;						// cartes panorama Montagne
	int panSea;							// cartes panorama Mer

	SDL_bool hovered;
	int      clicked;
} Player;

typedef struct
{
	SquareType* type;    // pointeur vers le type de case
	int position;
	int capacity;        // Nb de joueurs pouvant être sur la case
	int offsetY;         // Elevation aléatoire de la case pour donner un côté organique au plateau

	SDL_bool hovered;
	int      clicked;
} Square;

typedef struct
{
	SDL_Point origin;
	float scale;
} Camera;

extern Ressources ressources;

void load_ressources(TextureMgr* textureMgr);

#endif

/*
Types de case :
 0 : Relai / Inn
 1 : Echoppe / Shop
 2 : Source chaude / Hot water spring
 3 : Temple / Temple
 4 : Rencontre / Encounter
 5 : Ferme / Farm
 6 : Panorama Rizière / Rice field Panorama
 7 : Panorama Montagne / Mountain panorama
 8 : Panorama Mer / Seaside Panorama
*/
