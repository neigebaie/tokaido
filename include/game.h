#ifndef GAME_H_
#define GAME_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <utility.h>
#include <game.h>
#include <gui.h>

// camera
#define CAMERA_MIN_ZOOM 0.5
#define CAMERA_MAX_ZOOM 1.25

// resources
#define SQUARES 10
#define FOODS 14
#define ITEMS 24
#define ITEM_CATS 4
#define ENCOUNTERS 7
#define TRAVELERS 10

// board
#define BOARD_PLAYERS 5
#define BOARD_SQUARES 55

// SQUARE ID
typedef enum
{
	SQUARE_INN,
	SQUARE_SHOP,
	SQUARE_HOTSPRING,
	SQUARE_TEMPLE,
	SQUARE_ENCOUNTER,
	SQUARE_FARM,
	SQUARE_PAN_RICE,
	SQUARE_PAN_MOUNT,
	SQUARE_PAN_SEA
} SquareId;

typedef enum
{
	TRAVELER_SATSUKI,
	TRAVELER_HIROSHIGE,
	TRAVELER_CHUUBEI,
	TRAVELER_MITSUKUNI,
	TRAVELER_SASAYAKKO,
	TRAVELER_UMEGAE,
	TRAVELER_KINKO,
	TRAVELER_HIROTADA,
	TRAVELER_ZEN_EMON,
	TRAVELER_YOSHIYASU
} TravelerId;

typedef struct
{
	char name[100]; // nom de la rencontre
	Sprite* sprite;
} Encounter;

typedef struct
{
	char name[100]; // nom de la catégorie
	Sprite* sprite;
	int id;
} ItemCategory;

typedef struct
{
	int id;
	char name[100]; // nom du souvenir
	Sprite* sprite;
	int price;
	ItemCategory category;
} Item;

typedef struct
{
	char name[100]; // nom du repas
	Sprite* sprite;
	int price;
} Food;

typedef struct
{
	char name[100]; // nom de la case
	SquareId id;
	Sprite sprite;
	SDL_Color color;
} SquareType;

typedef struct
{
	char name[100]; // nom du voyageur
	Sprite sprite;
	int startCoins;
	TravelerId id;
} Traveler;

typedef struct
{
	Encounter*		encounters[ENCOUNTERS];  // rencontres
	Food*					foods[FOODS];            // nourritures
	Item*					items[ITEMS];            // souvenirs
	ItemCategory* itemCats[ITEM_CATS];     // catégories
	SquareType*		squareTypes[SQUARES];    // Cases
	Traveler*			travelers[TRAVELERS];    // voyageurs
} Resources;


typedef struct
{
	Traveler traveler;     // personnage choisi
	Text* nameTag;

	char nickname[100];			// pseudo du joueur si jeu en LAN/WAN
	SDL_bool isHuman;				// joueur IA ou humain
	// SDL_bool isLocal;				// joueur local ou réseau

	int position;						// position du joueur sur le plateau
	int roadDist;						// éloignement de la route

	int bundleToken;        // points de victoire accumulés (jeton balûchon)
	int coins;              // pièces possédées
	int templeCoins;        // pièces données au temple
	int hotSpringCount;     // nombre de passages à une source chaude
	int innCoins;           // nombre de pièces dépensées pour les repas

	Food foods[50];
	int  foodCount;

	Item items[50];
	int  itemCount;

	Encounter encounters[50];
	int       encounterCount;

	int panRice;						// cartes panorama Rizière
	int panMount;						// cartes panorama Montagne
	int panSea;							// cartes panorama Mer

	State state;
} Player;

typedef struct
{
	// Cette structure résume tous les gains d'un joueur lors de son tour.
	// Elle permet d'afficher le petit résumé sur la droite de l'écran pour les
	// PNJ ainsi que les joueurs humains jouant en LAN sur une autre machine.
	int bundleToken;
	int coins;
	int templeCoins;

	Food foods[5];
	int foodCount;

	Item items[5];
	int itemCount;

	Encounter encounters[50];
	int encounterCount;

	int panRice;
	int panMount;
	int panSea;
} Recap;

typedef struct
{
	SquareType type;    // type de case
	int position;
	int capacity;       // Nb de joueurs pouvant être sur la case

	State state;
} Square;

typedef struct
{
	SDL_Point origin;
	float scale;
} Camera;

extern Resources resources;

int tk_from_collection(Item newItem, Item* items, int itemCount);
void reset_recap(Recap* recap);
void load_resources();

#endif

/*
Types de case : (+traduction)
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
