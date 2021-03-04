#include "helper.h"
SDL_Window   	*Window    = NULL;
SDL_Renderer 	*Renderer  = NULL;

void init(void)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	Window = SDL_CreateWindow("", 0, 0, 0, 0, SDL_WINDOW_HIDDEN);

	//BEGIN ICON
	SDL_Surface *icon = NULL;
	icon = IMG_Load("gfx/icon.png");
	SDL_SetWindowIcon(Window, icon);
	SDL_FreeSurface(icon);
	//BEGIN ICON
	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_SOFTWARE); // SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
}

void exit_(void)
{
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	TTF_Quit();
	SDL_Quit();
}

// Il manque tous les tests à l'initialisation
