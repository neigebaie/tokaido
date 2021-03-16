#include "gui.h"
#include "utility.h"

/*

But du fichier gui.c :
 - Création bouton
 - Création Rect avec centrage sur un autre Rect, ancrage à l'écran, etc.
 - Création de texture de texte

 - Affichage du menu principal
 - Affichage du leaderboard

*/

Gui gui;

SDL_Rect centered_rect(SDL_Texture *texture, SDL_Rect rectParent, float scale)
{
	SDL_Rect rectChild;
	SDL_QueryTexture(texture, NULL, NULL, &rectChild.w, &rectChild.h);
	rectChild.w *= scale;
	rectChild.h *= scale;
	rectChild.x = rectParent.x + (rectParent.w/2 - rectChild.w/2);
	rectChild.y = rectParent.y + (rectParent.h/2 - rectChild.h/2);
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

void create_main_menu(void)
{
	gui.cursor = load_texture("ressources/gfx/gui/cursor.png");
	gui.title = load_texture("ressources/gfx/gui/title.png");
	gui.button = load_texture("ressources/gfx/gui/button.png");
	gui.board = load_texture("ressources/gfx/board.png");

	SDL_QueryTexture(gui.title, NULL, NULL, &gui.titleRect.w, &gui.titleRect.h);
	gui.titleRect.x = WINDOW_WIDTH/2 - gui.titleRect.w/2;
	gui.titleRect.y = WINDOW_HEIGHT* 0.07;

	SDL_QueryTexture(gui.button, NULL, NULL, &gui.mMenuBtRect[0].w, &gui.mMenuBtRect[0].h);
	gui.mMenuBtRect[0].w /= 4;
	gui.mMenuBtRect[0].h /= 4;
	gui.mMenuBtRect[0].x = WINDOW_WIDTH/2 - gui.mMenuBtRect[0].w/2;
	gui.mMenuBtRect[0].y = WINDOW_HEIGHT*0.5;


	// place les autres boutons en fonction du premier
	for (int i = 1; i < 5; i++)
	{
		gui.mMenuBtRect[i].x = gui.mMenuBtRect[0].x;
		gui.mMenuBtRect[i].y = gui.mMenuBtRect[0].y + 100 * i;
		gui.mMenuBtRect[i].w = gui.mMenuBtRect[0].w;
		gui.mMenuBtRect[i].h = gui.mMenuBtRect[0].h;
	}

	gui.mMenuTex[0] = create_texture_from_str("Solo", 255, 255, 255);
	gui.mMenuTex[1] = create_texture_from_str("Multijoueur", 255, 255, 255);
	gui.mMenuTex[2] = create_texture_from_str("Archives", 255, 255, 255);
	gui.mMenuTex[3] = create_texture_from_str("Options...", 255, 255, 255);
	gui.mMenuTex[4] = create_texture_from_str("Quitter le jeu", 255, 255, 255);

	for (int i = 0; i < 5; i++)
	{
		gui.mMenuTextRect[i] = centered_rect(gui.mMenuTex[i], gui.mMenuBtRect[i], 0.5);
	}
}
