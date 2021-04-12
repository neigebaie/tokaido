#include "gui.h"

/*
But du fichier gui.c :
 - Création bouton
 - Création Rect avec centrage sur un autre Rect, ancrage à l'écran, etc.
 - Création de texture de texte

 - Affichage des menus
 - Affichage du leaderboard
*/

Gui gui;

SDL_Rect* centered_rect(SDL_Texture *texture, SDL_Rect* rectParent, float scale)
{
	SDL_Rect* rectChild = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	SDL_QueryTexture(texture, NULL, NULL, &rectChild->w, &rectChild->h);
	rectChild->w *= scale;
	rectChild->h *= scale;
	rectChild->x = rectParent->x + (rectParent->w/2 - rectChild->w/2);
	rectChild->y = rectParent->y + (rectParent->h/2 - rectChild->h/2);
	return rectChild;
}

SDL_Texture* create_texture_from_str(const char *text, int r, int g, int b)
{
	SDL_Surface *surface = NULL;
	SDL_Texture *texture = NULL;
	SDL_Color textColor = { r, g, b, 255 };

	surface = TTF_RenderUTF8_Blended(font, text, textColor);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}

SDL_Rect* rect(int x, int y, int w, int h) {
	SDL_Rect* rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
	return rect;
}

Gui* gui_init(void)
{
	Gui* gui = (Gui*)malloc(sizeof(Gui));

	SDL_Texture* atlas = load_texture("ressources/gfx/gui/cursor.png");

	// cursor
	gui->cursor = (Sprite*)malloc(sizeof(Sprite));
	gui->cursor->atlas = atlas;
	gui->cursor->atlasPos = rect(0, 0, 128, 128);
	gui->cursor->rect     = rect(0, 0, 64, 64);

	// btnBack
	gui->btnBack = (Sprite*)malloc(sizeof(Sprite));
	gui->btnBack->atlas = atlas;
	gui->btnBack->atlasPos = rect(0, 0, 0, 0);
	gui->btnBack->rect     = rect(0, 0, 0, 0);


	// MENU_MAIN : MENU PRINCIPAL

	// title
	gui->title = (Sprite*)malloc(sizeof(Sprite));
	gui->title->atlas = atlas;
	gui->title->atlasPos = rect(0, 0, 0, 0);
	gui->title->rect     = rect(0, 0, 0, 0);

	// btnSolo
	gui->btnSolo = (Sprite*)malloc(sizeof(Sprite));
	gui->btnSolo->atlas = atlas;
	gui->btnSolo->atlasPos = rect(0, 0, 0, 0);
	gui->btnSolo->rect     = rect(0, 0, 0, 0);

	// btnMultiplayer
	gui->btnMultiplayer = (Sprite*)malloc(sizeof(Sprite));
	gui->btnMultiplayer->atlas = atlas;
	gui->btnMultiplayer->atlasPos = rect(0, 0, 0, 0);
	gui->btnMultiplayer->rect     = rect(0, 0, 0, 0);

	// btnArchives
	gui->btnArchives = (Sprite*)malloc(sizeof(Sprite));
	gui->btnArchives->atlas = atlas;
	gui->btnArchives->atlasPos = rect(0, 0, 0, 0);
	gui->btnArchives->rect     = rect(0, 0, 0, 0);

	// btnSettings
	gui->btnSettings = (Sprite*)malloc(sizeof(Sprite));
	gui->btnSettings->atlas = atlas;
	gui->btnSettings->atlasPos = rect(0, 0, 0, 0);
	gui->btnSettings->rect     = rect(0, 0, 0, 0);

	// btnQuit
	gui->btnQuit = (Sprite*)malloc(sizeof(Sprite));
	gui->btnQuit->atlas = atlas;
	gui->btnQuit->atlasPos = rect(0, 0, 0, 0);
	gui->btnQuit->rect     = rect(0, 0, 0, 0);


	// MENU_LOGIN : MENU DE CONNEXION

	// textUsername
	gui->textLogin = (Sprite*)malloc(sizeof(Sprite));
	gui->textLogin->atlas = atlas;
	gui->textLogin->atlasPos = rect(0, 0, 0, 0);
	gui->textLogin->rect     = rect(0, 0, 0, 0);

	// textUsername
	gui->textUsername = (Sprite*)malloc(sizeof(Sprite));
	gui->textUsername->atlas = atlas;
	gui->textUsername->atlasPos = rect(0, 0, 0, 0);
	gui->textUsername->rect     = rect(0, 0, 0, 0);

	// btnQuit
	gui->textPassword = (Sprite*)malloc(sizeof(Sprite));
	gui->textPassword->atlas = atlas;
	gui->textPassword->atlasPos = rect(0, 0, 0, 0);
	gui->textPassword->rect     = rect(0, 0, 0, 0);

	return gui;
}

void draw_main_menu(Gui* gui)
{
	SDL_RenderCopy(renderer, gui->title->atlas, gui->title->atlasPos, gui->title->rect);

	SDL_RenderCopy(renderer, gui->btnSolo->atlas, gui->btnSolo->atlasPos, gui->btnSolo->rect);
	SDL_RenderCopy(renderer, gui->btnMultiplayer->atlas, gui->btnMultiplayer->atlasPos, gui->btnMultiplayer->rect);
	// SDL_RenderCopy(renderer, gui->btnArchives->atlas, gui->btnArchives->atlasPos, gui->btnArchives->rect);
	SDL_RenderCopy(renderer, gui->btnSettings->atlas, gui->btnSettings->atlasPos, gui->btnSettings->rect);
	SDL_RenderCopy(renderer, gui->btnQuit->atlas, gui->btnQuit->atlasPos, gui->btnQuit->rect);
}

void draw_login_menu(Gui* gui)
{
	SDL_RenderCopy(renderer, gui->textLogin->atlas, gui->textLogin->atlasPos, gui->textLogin->rect);
	SDL_RenderCopy(renderer, gui->textUsername->atlas, gui->textUsername->atlasPos, gui->textUsername->rect);
	SDL_RenderCopy(renderer, gui->textPassword->atlas, gui->textPassword->atlasPos, gui->textPassword->rect);
}
