#ifndef GUI_H_
#define GUI_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "utility.h"

#define BTN_NB 7

typedef struct
{
	Sprite* bg;
	Sprite* text;
	SDL_bool hovered;
	SDL_bool clicked;
} Button;

typedef struct
{
		// Screen dimensions
		int screenWidth;
		int screenHeight;

		Button* btnList[BTN_NB];

		// Generic UI elements
		Sprite*     cursor;
		Sprite*     btn;
		Button*     btnNext;
		Button*     btnBack;


		// MENU_MAIN : MENU PRINCIPAL
		Sprite*     title;
		Button*     btnSolo;
		Button*     btnMultiplayer;
		Button*     btnArchives;
		Button*     btnSettings;
		Button*     btnQuit;


		// MENU_LOGIN : MENU DE CONNEXION
		Sprite*     textLogin;
		Sprite*     textUsername;
		Sprite*     textPassword;
		Button*     btnLogin;


		// MENU_SIGNUP : MENU DE CREATION DE COMPTE
		Sprite*     textSignUp;
		Sprite*     textRepeatPassword;
		Button*     btnSignUp;

} Gui;

// extern Gui gui;

Sprite* new_sprite_from_str(const char* text, int r, int g, int b, int a);
void center_rect(SDL_Rect* rectChild, SDL_Rect* rectParent, float scale);

Button* new_button(const char* text, int r, int g, int b, int a, Sprite* bgSprite, float textScale);

void print_rect(SDL_Rect* rect);
void draw_button(Button* button);

Gui* gui_init(void);

void draw_main_menu(Gui* gui);
void draw_login_menu(Gui* gui);
void draw_signup_menu(Gui* gui);

#endif
