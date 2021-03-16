#ifndef BOARD_H_
#define BOARD_H_

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utility.h"

// ressources
#define SQUARES 9
#define FOODS 14
#define ITEMS 24
#define ITEM_CATS 4
#define ENCOUNTERS 7
#define TRAVELERS 10
// board
#define BOARD_PLAYERS 5
#define BOARD_SQUARES 55

typedef struct
{
	SDL_Rect rect;
	char name[100];					// nom de la case
} SquareRes;

typedef struct
{
	char name[100];					// nom du repas
	int price;
} FoodRes;

typedef struct
{
	char name[100];					// nom du souvenir
	int price;
	int category;
} ItemRes;

typedef struct
{
	char name[100];					// nom de la categorie de souvenir
	int startCoins;
} TravelerRes;

typedef struct
{
	char name[100];					// nom de la categorie de souvenir
	int giveItem;						// Artisan				→	x:quantity
	int givePanCard;				// Guide					→	0:nothing  1:rice  2:mount  3:sea
	int giveBundleTk;				// Samouraï				→	x:quantity
	int giveCoin;						// Noble					→	x:quantity
	int giveTemple;					// Prêtre Shinto	→	x:quantity
} EncounterRes;

typedef struct
{

	SquareRes 		squares[SQUARES];				// Cases
	SDL_Texture		*squareTex;

	FoodRes 			foods[FOODS];						// nourritures
	SDL_Texture		*foodTex;

	ItemRes 			items[ITEMS];						// souvenirs
	SDL_Texture		*itemTex;
	SDL_Texture		*itemCatTex;

	EncounterRes 	encounters[ENCOUNTERS];	// rencontres
	SDL_Texture		*encounterTex;

	TravelerRes		travelers[TRAVELERS];		// voyageurs
	SDL_Texture		*travelerTex;

} Ressources;


typedef struct
{
	int traveler;						// personnage choisi

	char nickname[100];					// pseudo du joueur si jeu en LAN/WAN
	SDL_bool isHuman;				// joueur IA ou humain

	int position;						// position du joueur sur le plateau

	int bundleToken;				// points de victoire accumulés (jeton balûchon)
	int coins;							// pièces possédées
	int templeCoins;				// pièces données au temple
	int hotSpring;					// nombre de passages à une source chaude

	int foods[50];
	int foodCount;

	int items[50];
	int itemCount;

	int encounters[50];
	int encounterCount;

	int panRice;						// cartes panorama Rizière
	int panMount;						// cartes panorama Montagne
	int panSea;							// cartes panorama Mer

} Player;

typedef struct
{
	int id;									// entier représentant le type de case (voir la table pour transcrire)
	int capacity;						// Nb de joueurs pouvant être sur la case
} Square;


typedef struct
{
	int playerCount;									// nb de joueurs sur le plateau
	Player players[BOARD_PLAYERS];		// Liste des joueurs

	int squareCount;
	Square squares[BOARD_SQUARES];

	int turn;													// Index du joueur qui joue ce tour
} Board;

extern Board board;

void load_squares(const char* path, Square *squares);
void save_board(Board board, const char* path);
void init_board(void);

void load_ressources(void);

void draw_bg(void);
void draw_board(Board board);
void draw_squares(int squareCount, Square squares[]);

void draw_test(void);

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
