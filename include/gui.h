#ifndef GUI_H_
#define GUI_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <utility.h>
#include <account.h>

#define TEXT_LEN 512

// action des boutons
typedef enum
{
	ACTION_NONE,
	ACTION_QUIT,
	ACTION_START_SOLO_1,
	ACTION_START_SOLO_2,
	ACTION_LOGIN,
	ACTION_LOGOUT,
	ACTION_SIGNUP,
	ACTION_DEL_ACC,
	ACTION_TEMPLE,
	ACTION_END_TURN
} Action;

typedef enum
{
	MENU_NONE,
	MENU_MAIN,
	MENU_LOGIN,
	MENU_SIGNUP,
	// MENU_ACCOUNT,
	// MENU_LOAD,
	// MENU_SAVE,
	MENU_CHAR_SEL,
	// MENU_RULES,
	MENU_ARCHIVES,
	MENU_BOARD
} MenuId;

typedef struct
{
	Sprite* sprite;
  char content[TEXT_LEN];
  SDL_Color color;
	float scale;
} Text;

typedef struct
{
	Sprite bg;
	Text* text;
	State state;
	Action action;
	MenuId nextMenuId;
} Button;

// zone de saisie
typedef struct
{
	Sprite bg;
	Text* text;
	int textLen;
	State state;
	SDL_bool isPassword;
	int nextTextboxId; // switch to the next textbox when <tab> hit
} Textbox;

typedef struct
{
	Sprite**  sprites;
	int       spriteCount;

	Text**    texts;
	int       textCount;

	Textbox** textboxes;
	int       textboxCount;

	Button**  buttons;
	int       buttonCount;
} Menu;

// regroupe tous les menus qui n'ont pas d'élements du jeu
typedef struct
{
	Menu* mainMenu;
	Menu* loginMenu;
	Menu* signupMenu;
	Menu* archivesMenu;
	Menu* charSelMenu;

	Menu* menus[MENU_BOARD];
} Gui;

// initialise tous les menus
Gui* init_gui();

// MENU
Menu* base_menu(int s, int t, int tb, int b);

Menu* new_main_menu();
Menu* new_login_menu();
Menu* new_signup_menu();
Menu* new_archives_menu();
Menu* new_char_sel_menu();

// affichage / mise à jour / destruction 
void draw_menu(Menu* menu);
void update_menu(Menu* menu);
void destroy_menu(Menu* menu);

// SPRITE
void draw_sprite(Sprite* sprite);

// BUTTON
Button* new_button(char* content, float scale, Action action, MenuId nextMenuId);
void draw_button(Button* button);
void button_action(Button* button, MenuId* menuId);
void destroy_button(Button* button);

// TEXT
Text* new_text(char* content, int r, int g, int b, float scale);
void update_text(Text* text);
void destroy_text(Text* text);

// TEXTBOX
Textbox* new_textbox(SDL_bool isPassword, int nextTextboxId);
void textbox_event(Textbox *textbox, SDL_Event* event);
void draw_textbox(Textbox* textbox);
void destroy_textbox(Textbox* textbox);

// FONCTION DEFINIE DANS BOARD.C
void end_turn();

#endif
