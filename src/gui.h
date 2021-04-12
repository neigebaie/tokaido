#ifndef GUI_H_
#define GUI_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "utility.h"

typedef struct
{
		// Generic UI elements
		Sprite*     cursor;
		Sprite*     btnBack;


		// MENU_MAIN : MENU PRINCIPAL
		Sprite*     title;
		Sprite*     btnSolo;
		Sprite*     btnMultiplayer;
		Sprite*     btnArchives;
		Sprite*     btnSettings;
		Sprite*     btnQuit;


		// MENU_LOGIN : MENU DE CONNEXION
		Sprite*     textLogin;
		Sprite*     textUsername;
		Sprite*     textPassword;

		// MENU_SIGNUP : MENU DE CREATION DE COMPTE

} Gui;

// extern Gui gui;

SDL_Texture* create_texture_from_str(const char *text, int r, int g, int b);
SDL_Rect* centered_rect(SDL_Texture *texture, SDL_Rect* rectParent, float scale);

Gui* gui_init(void);

void draw_main_menu(Gui* gui);
void draw_login_menu(Gui* gui);

#endif
