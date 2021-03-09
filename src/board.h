#ifndef BOARD_H_
#define BOARD_H_

#include <SDL2/SDL.h>
#include <stdio.h>

#define INN_COUNT 4
#define SQUARES_PER_INN 4

typedef struct
{
	int playerCount;				// nb de joueurs sur le plateau
	Player** players;				// Liste des joueurs
	Square squares;					// Cases
	int turn;								// Index du joueur qui joue ce tour
} Board;

typedef struct
{
	SDL_Texture playerTex;	// sprite du joueur
	char* playerName;				// nom du personnage
	char* nickname;					// pseudo du joueur si jeu en LAN/WAN
	SDL_bool isHuman;				// joueur IA ou humain

	int position;						// position du joueur sur le plateau

	int bundleToken;				// points de victoire accumulés (jeton balûchon)
	int coins;							// pièces possédées
	int templeCoins;				// pièces données au temple

	Food* foods;						// nourritures goûtées
	Item* items;						// objets achetés
	Traveler* travlers;			// objets achetés

	int panRice;						// cartes panorama Rizière
	int panMount;						// cartes panorama Montagne
	int panSea;							// cartes panorama Mer

	Bonus bonus;						// bonus du personnage choisi (à voir)
} Player;

typedef struct {
	int type;								// entier représentant le type de case (voir la table pour transcrire)
	int position;						// position de la case sur le plateau
	int capacity;						// Nb de joueurs pouvant être sur la case
} Square;

Board load_board(const char* path);
void load_save(Board board, const char* path);

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
