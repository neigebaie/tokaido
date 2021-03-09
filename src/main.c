// Tokaido by neigebaie (C) 2021
#include "utility.h"

SDL_Texture* load_texture(const char *path);
SDL_Texture* create_texture_from_str(const char *text);
SDL_Rect centered_rect(SDL_Texture *texture, SDL_Rect rectParent);

SDL_Rect centered_rect(SDL_Texture *texture, SDL_Rect rectParent)
{
	SDL_Rect rectChild;
	SDL_QueryTexture(texture, NULL, NULL, &rectChild.w, &rectChild.h);
	rectChild.x = rectParent.x + (rectParent.w/2 - rectChild.w/2);
	rectChild.y = rectParent.y + (rectParent.h/2 - rectChild.h/2);
	return rectChild;
}

SDL_Texture* create_texture_from_str(const char *text)
{
	SDL_Surface *surface = NULL;
	SDL_Texture *texture = NULL;
	SDL_Color textColor = { 255, 255, 255, 255 };

	surface = TTF_RenderText_Blended(font, text, textColor);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}

SDL_Texture* load_texture(const char *path)
{
	SDL_Surface *surface = NULL;
	SDL_Texture *texture = NULL;
	surface = IMG_Load(path);
	if (surface == NULL)
		exit_with_error("Création de surface échouée");
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL)
		exit_with_error("Création de texture échouée");
	SDL_FreeSurface(surface);
	return texture;
}

int main(int argc, const char *argv[])
{
	init();
	SDL_ShowCursor(0);

	// load_textures();

	// Textures
	SDL_Point mousePos;

	SDL_Texture *cursor = NULL;
	SDL_Texture *title = NULL;
	SDL_Texture *button = NULL;

	cursor = load_texture("ressources/gfx/gui/cursor.png");
	title = load_texture("ressources/gfx/gui/title.png");
	button = load_texture("ressources/gfx/gui/button.png");

	SDL_Rect mouseRect = {0, 0, 0, 0};
	SDL_QueryTexture(cursor, NULL, NULL, &mouseRect.w, &mouseRect.h);
	mouseRect.w /= 2;
	mouseRect.h /= 2;

	SDL_Rect titleRect = {0, 0, 0, 0};
	SDL_QueryTexture(title, NULL, NULL, &titleRect.w, &titleRect.h);
	titleRect.x = WINDOW_WIDTH/2 - titleRect.w/2;
	titleRect.y = WINDOW_HEIGHT/6;

	SDL_Rect buttonRect = {0, 0, 0, 0};
	SDL_QueryTexture(button, NULL, NULL, &buttonRect.w, &buttonRect.h);
	buttonRect.w /= 4;
	buttonRect.h /= 4;
	buttonRect.x = WINDOW_WIDTH/2 - buttonRect.w/2;
	buttonRect.y = WINDOW_HEIGHT*0.6;
	SDL_Rect buttonRect1 = {buttonRect.x, buttonRect.y + 100 * 1, buttonRect.w, buttonRect.h};
	SDL_Rect buttonRect2 = {buttonRect.x, buttonRect.y + 100 * 2, buttonRect.w, buttonRect.h};

	SDL_Texture *jouerTex = create_texture_from_str("JOUER OFFLINE");
	SDL_Rect		 jouerRect = centered_rect(jouerTex, buttonRect);

	SDL_Texture *jouerOTex = create_texture_from_str("JOUER ONLINE");
	SDL_Rect		 jouerORect = centered_rect(jouerOTex, buttonRect1);

	SDL_Texture *quitTex = create_texture_from_str("QUITTER");
	SDL_Rect		 quitRect = centered_rect(quitTex, buttonRect2);


	SDL_bool program_launched = SDL_TRUE;
	SDL_bool update = SDL_TRUE;

	while (program_launched)
	{
		SDL_Event event;
		SDL_GetMouseState(&mousePos.x, &mousePos.y);
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
						case SDLK_RETURN:
							printf("Vous avez appuyé sur Entrer\n");
							update = SDL_TRUE;
							break;
						case SDLK_ESCAPE:
							program_launched = SDL_FALSE;
							break;
					}
					break;
				case SDL_QUIT:
					program_launched = SDL_FALSE;
					break;
				default:
					break;
			}
		}
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		if (update)
		{
			SDL_RenderCopy(renderer, title, NULL, &titleRect);
			SDL_RenderCopy(renderer, button, NULL, &buttonRect);
			SDL_RenderCopy(renderer, button, NULL, &buttonRect1);
			SDL_RenderCopy(renderer, button, NULL, &buttonRect2);
			SDL_RenderCopy(renderer, jouerTex, NULL, &jouerRect);
			SDL_RenderCopy(renderer, jouerOTex, NULL, &jouerORect);
			SDL_RenderCopy(renderer, quitTex, NULL, &quitRect);
			// update = SDL_FALSE;
		}

		mouseRect.x = mousePos.x;
		mouseRect.y = mousePos.y;
		SDL_RenderCopy(renderer, cursor, NULL, &mouseRect); // cursor toujours au dessus

		SDL_RenderPresent(renderer);
	}

	exit_with_success();
	return EXIT_SUCCESS;
}
