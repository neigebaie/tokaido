#include "utility.h"

SDL_Window   	*window    = NULL;
SDL_Renderer 	*renderer  = NULL;
TTF_Font 			*font      = NULL;

void init(void)
{
	// Initialisation SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		exit_with_error("Initialisation SDL échouée");

	// Création de la fenêtre (SDL_Window)
	window = SDL_CreateWindow(
		"Tokaido",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_FULLSCREEN // SDL_WINDOW_SHOWN : pour la version fenêtrée
	);

	if (window == NULL)
		exit_with_error("Création de la fenêtre échouée");

	// Chargement de l'icon
	SDL_Surface *icon = NULL;
	icon = IMG_Load("ressources/gfx/gui/icon.png");
	SDL_SetWindowIcon(window, icon);
	SDL_FreeSurface(icon);

	// Création du renderer (SDL_Renderer)
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE); // SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC

	if (renderer == NULL)
		exit_with_error("Création du Renderer échouée");

	// Initialisation SDL_TTF
	TTF_Init();
	font = TTF_OpenFont("ressources/fonts/Buried K9.ttf", 40);
	if (font == NULL)
		exit_with_error("\ressources/fonts/Buried K9.ttf\" n'a pas pu être chargé");
}


void exit_with_error(const char *message)
{
	// Affiche un message d'erreur et quitte le programme
	SDL_Log("\e[31m ERREUR 🥺 : %s > %s\e[37m\n", message, SDL_GetError());
	exit(EXIT_FAILURE);
}

void exit_with_success(void)
{
	// Nettoyage à la sortie du programme
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
	// printf("\e[34m Au revoir !\e[37m\n"); // debug
}
