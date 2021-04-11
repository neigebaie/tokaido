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

	gui->atlas = load_texture("ressources/gfx/gui/cursor.png");

	// cursor
	gui->cursor = (GuiElement*)malloc(sizeof(GuiElement));
	gui->cursor->atlasPos = rect(0, 0, 0, 0);
	gui->cursor->rect     = rect(0, 0, 0, 0);

	// btnBack
	gui->btnBack = (GuiElement*)malloc(sizeof(GuiElement));
	gui->btnBack->atlasPos = rect(0, 0, 0, 0);
	gui->btnBack->rect     = rect(0, 0, 0, 0);


	// MENU_MAIN : MENU PRINCIPAL

	// title
	gui->title = (GuiElement*)malloc(sizeof(GuiElement));
	gui->title->atlasPos = rect(0, 0, 0, 0);
	gui->title->rect     = rect(0, 0, 0, 0);

	// btnSolo
	gui->btnSolo = (GuiElement*)malloc(sizeof(GuiElement));
	gui->btnSolo->atlasPos = rect(0, 0, 0, 0);
	gui->btnSolo->rect     = rect(0, 0, 0, 0);

	// btnMultiplayer
	gui->btnMultiplayer = (GuiElement*)malloc(sizeof(GuiElement));
	gui->btnMultiplayer->atlasPos = rect(0, 0, 0, 0);
	gui->btnMultiplayer->rect     = rect(0, 0, 0, 0);

	// btnArchives
	gui->btnArchives = (GuiElement*)malloc(sizeof(GuiElement));
	gui->btnArchives->atlasPos = rect(0, 0, 0, 0);
	gui->btnArchives->rect     = rect(0, 0, 0, 0);

	// btnSettings
	gui->btnSettings = (GuiElement*)malloc(sizeof(GuiElement));
	gui->btnSettings->atlasPos = rect(0, 0, 0, 0);
	gui->btnSettings->rect     = rect(0, 0, 0, 0);

	// btnQuit
	gui->btnQuit = (GuiElement*)malloc(sizeof(GuiElement));
	gui->btnQuit->atlasPos = rect(0, 0, 0, 0);
	gui->btnQuit->rect     = rect(0, 0, 0, 0);


	// MENU_LOGIN : MENU DE CONNEXION

	// textUsername
	gui->textUsername = (GuiElement*)malloc(sizeof(GuiElement));
	gui->textUsername->atlasPos = rect(0, 0, 0, 0);
	gui->textUsername->rect     = rect(0, 0, 0, 0);

	// btnQuit
	gui->textPassword = (GuiElement*)malloc(sizeof(GuiElement));
	gui->textPassword->atlasPos = rect(0, 0, 0, 0);
	gui->textPassword->rect     = rect(0, 0, 0, 0);

	return gui;
}

void draw_main_menu(void)
{
	printf("\n");
}

void draw_login_menu(void)
{
	printf("\n");
}
