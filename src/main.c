// Tokaido by neigebaie (C) 2021
#include <stdio.h>
#include <SDL.h>

void SDL_ExitWithError(const char *message);

int main(int argc, char const *argv[])
{
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		SDL_ExitWithError("ERREUR : Initialisation SDL > %s\n", SDL_GetError());

	window = SDL_CreateWindow("Tokaido 🎲",
				  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				  640, 480,
				  SDL_WINDOW_SHOWN);

	if (window == NULL)
		SDL_ExitWithError("ERREUR : Création de la fenêtre > %s\n", SDL_GetError());

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

	SDL_Delay(10000); // juste un délai pour pouvoir voir la fenêtre.

	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}

void SDL_ExitWithError(const char *message)
{
	SDL_Log(message);
	exit(EXIT_FAILURE);
}
