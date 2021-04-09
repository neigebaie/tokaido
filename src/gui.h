#ifndef GUI_H_
#define GUI_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "utility.h"

typedef struct
{
		SDL_Texture  *cursor;
		SDL_Texture  *title;
		SDL_Texture  *button;
		SDL_Texture	 *board;

		SDL_Rect 		 titleRect;

		SDL_Texture *mMenuTex[5];
		SDL_Rect	 	mMenuBtRect[5];
		SDL_Rect	 	mMenuTextRect[5];
		/* Ordre des boutons :
				0 : Solo
				1 : Multijoueur
				2 : Parties Archivées
				3 : Options...
				4 : Quitter le jeu
		*/
} Gui;

extern Gui gui;

void create_main_menu(void);
SDL_Texture* create_texture_from_str(const char *text, int r, int g, int b);
SDL_Rect centered_rect(SDL_Texture *texture, SDL_Rect rectParent, float scale);
void draw_login(void);
#endif
