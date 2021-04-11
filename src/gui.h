#ifndef GUI_H_
#define GUI_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "utility.h"

typedef struct {
		SDL_Rect* atlasPos; // position in the spritesheet (px)
    SDL_Rect* rect;     // position on screen (px)
} GuiElement;

typedef struct
{
		SDL_Texture  *atlas;

		// Generic UI elements
		GuiElement*     cursor;
		GuiElement*     btnBack;


		// MENU_MAIN : MENU PRINCIPAL
		GuiElement*     title;
		GuiElement*     btnSolo;
		GuiElement*     btnMultiplayer;
		GuiElement*     btnArchives;
		GuiElement*     btnSettings;
		GuiElement*     btnQuit;


		// MENU_LOGIN : MENU DE CONNEXION
		GuiElement*     textUsername;
		GuiElement*     textPassword;

		// MENU_SIGNUP : MENU DE CREATION DE COMPTE

} Gui;

// extern Gui gui;

SDL_Texture* create_texture_from_str(const char *text, int r, int g, int b);
SDL_Rect* centered_rect(SDL_Texture *texture, SDL_Rect* rectParent, float scale);

Gui* gui_init(void);

void draw_main_menu(void);
void draw_login_menu(void);

#endif
