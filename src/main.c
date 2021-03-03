// Tokaido by neigebaie (C) 2021
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

void SDL_ExitWithError(const char *message);

int main(int argc, char const *argv[])
{
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		SDL_ExitWithError("Initialisation SDL échouée");

	window = SDL_CreateWindow("Tokaido 🎲",
				  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				  678, 650,
				  SDL_WINDOW_SHOWN);

	if (window == NULL)
		SDL_ExitWithError("Création de la fenêtre échouée");

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

	if (renderer == NULL)
		SDL_ExitWithError("Création du Renderer échouée");

	SDL_Delay(100); // Sans le délai ça affiche rien ^^'
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	SDL_Surface *image = NULL;
	SDL_Texture *texture = NULL;

	image = SDL_LoadBMP("sprites/temple.bmp");

	texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);
	SDL_Rect rect;
	rect.x = 10;
	rect.y = 10;

	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);

	SDL_RenderCopy(renderer, texture, NULL, &rect);

	SDL_RenderPresent(renderer);

	// SDL_ExitWithError("Test de la fonction d'erreur.");
	SDL_Delay(5 * 1000); // juste un délai pour pouvoir voir la fenêtre.

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}

void SDL_ExitWithError(const char *message)
{
	SDL_Log("\e[31m ERREUR 🥺 : %s > %s\e[37m\n", message, SDL_GetError());
	exit(EXIT_FAILURE);
}
