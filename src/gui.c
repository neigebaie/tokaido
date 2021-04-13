#include "gui.h"

void center_rect(SDL_Rect* rectChild, SDL_Rect* rectParent, float scale)
{
	rectChild->w *= scale;
	rectChild->h *= scale;
	rectChild->x = rectParent->x + (rectParent->w/2 - rectChild->w/2);
	rectChild->y = rectParent->y + (rectParent->h/2 - rectChild->h/2);
}

Sprite* new_sprite_from_str(const char* text, int r, int g, int b, int a)
{
	SDL_Surface *surface = NULL;
	SDL_Texture *texture = NULL;
	SDL_Color textColor = { r, g, b, a };

	surface = TTF_RenderUTF8_Blended(font, text, textColor);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	Sprite* sprite = new_sprite(texture, new_rect(0, 0, 0, 0));
	SDL_QueryTexture(sprite->tex, NULL, NULL, &sprite->rect->w, &sprite->rect->h);
	SDL_QueryTexture(sprite->tex, NULL, NULL, &sprite->texPos->w, &sprite->texPos->h);

	return sprite;
}

Button* new_button(const char* text, int r, int g, int b, int a, Sprite* bgSprite, float textScale)
{
	Button* button     = (Button*)malloc(sizeof(Button));
	button->text       = (Sprite*)malloc(sizeof(Sprite));
	button->bg         = (Sprite*)malloc(sizeof(Sprite));
	// memcpy(button->bg, bgSprite, sizeof(Sprite));
	button->bg->tex    = bgSprite->tex;
	button->bg->texPos = new_rect(0, 0, bgSprite->texPos->w, bgSprite->texPos->h);
	button->bg->rect   = new_rect(0, 0, bgSprite->rect->w, bgSprite->rect->h);
	button->hovered    = SDL_FALSE;
	button->clicked    = SDL_FALSE;
	button->text       = new_sprite_from_str(text, r, g, b, 255);
	center_rect(button->text->rect, button->bg->rect, textScale);

	return button;
}

void print_rect(SDL_Rect* rect)
{
	printf("Rect : %4d %4d %4d %4d\n", rect->x, rect->y, rect->w, rect->h);
}

Gui* gui_init(void)
{
	Gui* gui = (Gui*)malloc(sizeof(Gui));

	SDL_Texture* tex = load_texture("ressources/gfx/gui/spritesheet.png");

	// Generic
	gui->cursor         = new_sprite(tex, new_rect(889, 308, 60, 47));
	gui->btn 		        = new_sprite(tex, new_rect(0, 0, 1319, 307));
	gui->btn->rect->w *= 0.25;
	gui->btn->rect->h *= 0.25;

	// MENU_MAIN : MENU PRINCIPAL

	gui->title 		      = new_sprite(tex, new_rect(0, 308, 888, 335));
	center_rect(gui->title->rect, new_rect(0, 150, 1920, 200), 1);

	gui->btnSolo        = new_button("Solo", 255, 255, 255, 255, gui->btn, 0.5);
	center_rect(gui->btnSolo->bg->rect, new_rect(0, 500, 1920, 200), 1);
	center_rect(gui->btnSolo->text->rect, gui->btnSolo->bg->rect, 1);
	// print_rect(gui->btnSolo->text->rect);

	gui->btnMultiplayer = new_button("Se connecter", 255, 255, 255, 255, gui->btn, 0.5);
	center_rect(gui->btnMultiplayer->bg->rect, new_rect(0, 600, 1920, 200), 1);
	center_rect(gui->btnMultiplayer->text->rect, gui->btnMultiplayer->bg->rect, 1);
	// print_rect(gui->btnMultiplayer->text->rect);

	gui->btnArchives    = new_button("Archives", 255, 255, 255, 255, gui->btn, 0.5);
	center_rect(gui->btnArchives->bg->rect, new_rect(0, 700, 1920, 200), 1);
	center_rect(gui->btnArchives->text->rect, gui->btnArchives->bg->rect, 1);

	gui->btnSettings    = new_button("Options", 255, 255, 255, 255, gui->btn, 0.5);
	center_rect(gui->btnSettings->bg->rect, new_rect(0, 800, 1920, 200), 1);
	center_rect(gui->btnSettings->text->rect, gui->btnSettings->bg->rect, 1);

	gui->btnQuit        = new_button("Quitter", 255, 255, 255, 255, gui->btn, 0.5);
	center_rect(gui->btnQuit->bg->rect, new_rect(0, 900, 1920, 200), 1);
	center_rect(gui->btnQuit->text->rect, gui->btnQuit->bg->rect, 1);

	gui->btnBack        = new_button("Retour", 255, 255, 255, 255, gui->btn, 0.5);
	center_rect(gui->btnBack->bg->rect, new_rect(0, 900, 1920, 200), 1);
	center_rect(gui->btnBack->text->rect, gui->btnBack->bg->rect, 1);

	gui->btnNext        = new_button("Suivant", 255, 255, 255, 255, gui->btn, 0.5);
	center_rect(gui->btnNext->bg->rect, new_rect(0, 800, 1920, 200), 1);
	center_rect(gui->btnNext->text->rect, gui->btnNext->bg->rect, 1);

	gui->btnSignUp      = new_button("Creer un compte", 255, 255, 255, 255, gui->btn, 0.5);
	center_rect(gui->btnSignUp->bg->rect, new_rect(0, 700, 1920, 200), 1);
	center_rect(gui->btnSignUp->text->rect, gui->btnSignUp->bg->rect, 1);

	// MENU_LOGIN : MENU DE CONNEXION

	gui->textLogin 		= new_sprite_from_str("Connexion au compte", 0, 0, 0, 255);
	center_rect(gui->textLogin->rect, new_rect(0, 150, 1920, 200), 1);

	gui->textUsername 		= new_sprite_from_str("Nom d'utilisateur : ", 0, 0, 0, 255);
	center_rect(gui->textUsername->rect, new_rect(0, 300, 1420, 200), 0.5);
	gui->textPassword 		= new_sprite_from_str("Mot de passe :", 0, 0, 0, 255);
	center_rect(gui->textPassword->rect, new_rect(0, 400, 1420, 200), 0.5);

	// MENU_SIGNUP : MENU DE CREATION DE COMPTE

	gui->textSignUp 		= new_sprite_from_str("Creation d'un nouveau compte", 0, 0, 0, 255);
	center_rect(gui->textSignUp->rect, new_rect(0, 150, 1920, 200), 1);

	gui->btnList[0] = gui->btnSolo;
	gui->btnList[1] = gui->btnMultiplayer;
	gui->btnList[2] = gui->btnArchives;
	gui->btnList[3] = gui->btnSettings;
	gui->btnList[4] = gui->btnQuit;
	gui->btnList[5] = gui->btnNext;
	// gui->btnList[6] = gui->btnBack;
	gui->btnList[6] = gui->btnSignUp;
	// gui->btnList[8] = gui->btnLogin;

	return gui;
}

void draw_button(Button* button)
{
	// SDL_Rect bgRect = {x, y, button->bg->rect->w * scale, button->bg->rect->h * scale};
	SDL_SetRenderDrawColor(renderer, 0, 0, 100, 50);
	// SDL_RenderFillRect(renderer, button->bg->rect);
	if (button->clicked)
		SDL_SetTextureColorMod(button->bg->tex, 150, 150, 150);
	else if (button->hovered)
		SDL_SetTextureColorMod(button->bg->tex, 200, 200, 200);
	SDL_RenderCopy(renderer, button->bg->tex, button->bg->texPos, button->bg->rect);
	SDL_SetTextureColorMod(button->bg->tex, 255, 255, 255);
	// SDL_SetRenderDrawColor(renderer, 255, 100, 100, 50);
	// SDL_RenderFillRect(renderer, button->text->rect);
	SDL_RenderCopy(renderer, button->text->tex, button->text->texPos, button->text->rect);
}

void draw_main_menu(Gui* gui)
{
	SDL_SetRenderDrawColor(renderer, 0, 255, 100, 50);
	// SDL_RenderFillRect(renderer, gui->title->rect);
	SDL_RenderCopy(renderer, gui->title->tex, gui->title->texPos, gui->title->rect);
	draw_button(gui->btnSolo);
	draw_button(gui->btnMultiplayer);
	draw_button(gui->btnArchives);
	draw_button(gui->btnSettings);
	draw_button(gui->btnQuit);
}

void draw_login_menu(Gui* gui)
{

	SDL_RenderCopy(renderer, gui->textLogin->tex, gui->textLogin->texPos, gui->textLogin->rect);
	SDL_RenderCopy(renderer, gui->textUsername->tex, gui->textUsername->texPos, gui->textUsername->rect);
	SDL_RenderCopy(renderer, gui->textPassword->tex, gui->textPassword->texPos, gui->textPassword->rect);
	draw_button(gui->btnNext);
	draw_button(gui->btnSignUp);
	draw_button(gui->btnBack);
	SDL_Rect rect = {gui->textPassword->rect->x + gui->textPassword->rect->w + 50, gui->textPassword->rect->y, 400, gui->textPassword->rect->h};
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 100);
	SDL_RenderFillRect(renderer, &rect);
	rect.y = gui->textUsername->rect->y;
	SDL_RenderFillRect(renderer, &rect);
}

void draw_signup_menu(Gui* gui)
{
	SDL_RenderCopy(renderer, gui->textSignUp->tex, gui->textSignUp->texPos, gui->textSignUp->rect);
	SDL_RenderCopy(renderer, gui->textUsername->tex, gui->textUsername->texPos, gui->textUsername->rect);
	SDL_RenderCopy(renderer, gui->textPassword->tex, gui->textPassword->texPos, gui->textPassword->rect);
	draw_button(gui->btnNext);
	draw_button(gui->btnBack);
	SDL_Rect rect = {gui->textPassword->rect->x + gui->textPassword->rect->w + 50, gui->textPassword->rect->y, 400, gui->textPassword->rect->h};
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 100);
	SDL_RenderFillRect(renderer, &rect);
	rect.y = gui->textUsername->rect->y;
	SDL_RenderFillRect(renderer, &rect);
}
