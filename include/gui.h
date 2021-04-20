#ifndef GUI_H_
#define GUI_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <utility.h>

#define TEXTBOX_SIZE 64
#define BTN_NB 10
#define TEXTOBX_NB 2

typedef struct
{
	Sprite*       bg;
	Sprite*       text;
	SDL_bool      hovered;
	int           clicked;
	// int (*action)(void);
} Button;

typedef struct
{
	Button*       box; // Même mécanique que pour un bouton donc je fais ça xD
	char*         text;
	int           textLen;
	SDL_bool      isPassword;
} Textbox;

typedef struct
{
	Sprite*       sprite;
	char*         text;
	SDL_Color*    color;
} TextInfo;

typedef struct
{
		Button*     btnList[BTN_NB];
		Button*     textboxList[TEXTOBX_NB];

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
		Textbox*    textboxUsername;
		Sprite*     textPassword;
		Textbox*    textboxPassword;
		Button*     btnLogin;
		TextInfo*   textInfo;


		// MENU_SIGNUP : MENU DE CREATION DE COMPTE
		Sprite*     textSignUp;
		Sprite*     textRepeatPassword;
		Button*     btnSignUp;

} Gui;

Gui* gui_init(TextureMgr* textureMgr);

Sprite* new_sprite_from_str(const char* text, int r, int g, int b, float scale);
Button* new_button(const char* text, int r, int g, int b, Sprite* bgSprite, float textScale);
Textbox* new_textbox(Sprite* bgSprite, SDL_bool isPassword);
TextInfo* new_text_info(int r, int g, int b, float textScale);

void center_rect(SDL_Rect* rectChild, SDL_Rect* rectParent);
Sprite* sprite_copy(Sprite* src);

void print_rect(SDL_Rect* rect);
void draw_button(Button* button);
void draw_sprite(Sprite* sprite);

void draw_main_menu(Gui* gui);
void draw_login_menu(Gui* gui);
void draw_signup_menu(Gui* gui);

void textbox_event(Textbox *textbox, SDL_Event event);
void textbox_update(Textbox *textbox);

void text_info_clear(TextInfo* textinfo);
void text_info_update(TextInfo* textinfo);

#endif
