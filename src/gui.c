#include "gui.h"

void center_rect(SDL_Rect* rectChild, SDL_Rect* rectParent, float scale)
{
	rectChild->w *= scale;
	rectChild->h *= scale;
	rectChild->x = rectParent->x + (rectParent->w/2 - rectChild->w/2);
	rectChild->y = rectParent->y + (rectParent->h/2 - rectChild->h/2);
}

// void anchor_rect(SDL_Rect* rectChild, SDL_Rect* rectParent, float scale);

Sprite* new_sprite_from_str(const char* text, int r, int g, int b)
{
	SDL_Surface *surface = NULL;
	SDL_Texture *texture = NULL;
	SDL_Color textColor = { r, g, b, 255 };

	surface = TTF_RenderUTF8_Blended(font, text, textColor);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	Sprite* sprite = new_sprite(texture, new_rect(0, 0, 0, 0));
	SDL_QueryTexture(sprite->tex, NULL, NULL, &sprite->rect->w, &sprite->rect->h);
	SDL_QueryTexture(sprite->tex, NULL, NULL, &sprite->texPos->w, &sprite->texPos->h);

	return sprite;
}

Button* new_button(const char* text, int r, int g, int b, Sprite* bgSprite, float textScale)
{
	Button* button     = (Button*)malloc(sizeof(Button));
	button->text       = (Sprite*)malloc(sizeof(Sprite));
	button->bg         = (Sprite*)malloc(sizeof(Sprite));
	// memcpy(button->bg, bgSprite, sizeof(Sprite));
	button->bg->tex    = bgSprite->tex;
	button->bg->texPos = new_rect(bgSprite->texPos->x, bgSprite->texPos->y, bgSprite->texPos->w, bgSprite->texPos->h);
	button->bg->rect   = new_rect(0, 0, bgSprite->rect->w, bgSprite->rect->h);
	button->hovered    = SDL_FALSE;
	button->clicked    = SDL_FALSE;
	button->text       = new_sprite_from_str(text, r, g, b);
	center_rect(button->text->rect, button->bg->rect, textScale);

	return button;
}

Textbox* new_textbox(Sprite* bgSprite, SDL_bool isPassword)
{
	Textbox* textbox = (Textbox*)malloc(sizeof(Textbox));
	textbox->box = new_button("", 255, 255, 255, bgSprite, 1);
	textbox->text = (char*)malloc(sizeof(char) * TEXTBOX_SIZE);
	textbox->textLen = 0;
	textbox->isPassword = isPassword;
	return textbox;
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
	Sprite* textboxBg   = new_sprite(tex, new_rect(0, 644, 1319, 307));
	textboxBg->rect->w *= 0.25;
	textboxBg->rect->h *= 0.25;
	gui->btn->rect->w *= 0.25;
	gui->btn->rect->h *= 0.25;

	// MENU_MAIN : MENU PRINCIPAL

	gui->title 		      = new_sprite(tex, new_rect(0, 308, 888, 335));
	center_rect(gui->title->rect, new_rect(0, 150, 1920, 200), 1);

	gui->btnSolo        = new_button("Solo", 255, 255, 255, gui->btn, 0.5);
	center_rect(gui->btnSolo->bg->rect, new_rect(0, 500, 1920, 200), 1);
	center_rect(gui->btnSolo->text->rect, gui->btnSolo->bg->rect, 1);
	// print_rect(gui->btnSolo->text->rect);

	gui->btnMultiplayer = new_button("Se connecter", 255, 255, 255, gui->btn, 0.5);
	center_rect(gui->btnMultiplayer->bg->rect, new_rect(0, 600, 1920, 200), 1);
	center_rect(gui->btnMultiplayer->text->rect, gui->btnMultiplayer->bg->rect, 1);
	// print_rect(gui->btnMultiplayer->text->rect);

	gui->btnArchives    = new_button("Archives", 255, 255, 255, gui->btn, 0.5);
	center_rect(gui->btnArchives->bg->rect, new_rect(0, 700, 1920, 200), 1);
	center_rect(gui->btnArchives->text->rect, gui->btnArchives->bg->rect, 1);

	gui->btnSettings    = new_button("Options", 255, 255, 255, gui->btn, 0.5);
	center_rect(gui->btnSettings->bg->rect, new_rect(0, 800, 1920, 200), 1);
	center_rect(gui->btnSettings->text->rect, gui->btnSettings->bg->rect, 1);

	gui->btnQuit        = new_button("Quitter", 255, 255, 255, gui->btn, 0.5);
	center_rect(gui->btnQuit->bg->rect, new_rect(0, 900, 1920, 200), 1);
	center_rect(gui->btnQuit->text->rect, gui->btnQuit->bg->rect, 1);

	gui->btnBack        = new_button("Retour", 255, 255, 255, gui->btn, 0.5);
	center_rect(gui->btnBack->bg->rect, new_rect(0, 900, 1920, 200), 1);
	center_rect(gui->btnBack->text->rect, gui->btnBack->bg->rect, 1);

	gui->btnNext        = new_button("Suivant", 255, 255, 255, gui->btn, 0.5);
	center_rect(gui->btnNext->bg->rect, new_rect(0, 800, 1920, 200), 1);
	center_rect(gui->btnNext->text->rect, gui->btnNext->bg->rect, 1);

	gui->btnSignUp      = new_button("Creer un compte", 255, 255, 255, gui->btn, 0.5);
	center_rect(gui->btnSignUp->bg->rect, new_rect(0, 700, 1920, 200), 1);
	center_rect(gui->btnSignUp->text->rect, gui->btnSignUp->bg->rect, 1);

	// MENU_LOGIN : MENU DE CONNEXION

	gui->textLogin = new_sprite_from_str("Connexion au compte", 0, 0, 0);
	center_rect(gui->textLogin->rect, new_rect(0, 150, 1920, 200), 1);

	gui->textUsername = new_sprite_from_str("Nom d'utilisateur : ", 0, 0, 0);
	center_rect(gui->textUsername->rect, new_rect(0, 300, 1420, 200), 0.5);
	gui->textboxUsername = new_textbox(textboxBg, SDL_FALSE);
	gui->textboxUsername->box->bg->rect->x = gui->textUsername->rect->x + gui->textUsername->rect->w + 50;
	gui->textboxUsername->box->bg->rect->y = gui->textUsername->rect->y - 15;
	gui->textboxUsername->box->bg->rect->w = 500;
	gui->textboxUsername->box->bg->rect->h = 80;

	gui->textPassword = new_sprite_from_str("Mot de passe :", 0, 0, 0);
	center_rect(gui->textPassword->rect, new_rect(0, 400, 1420, 200), 0.5);
	gui->textboxPassword = new_textbox(textboxBg, SDL_TRUE);
	gui->textboxPassword->box->bg->rect->x = gui->textUsername->rect->x + gui->textUsername->rect->w + 50;
	gui->textboxPassword->box->bg->rect->y = gui->textPassword->rect->y - 15;
	gui->textboxPassword->box->bg->rect->w = 500;
	gui->textboxPassword->box->bg->rect->h = 80;

	gui->textInfo = new_sprite_from_str("A É È à é è", 0, 0, 0);
	center_rect(gui->textInfo->rect, new_rect(0, 500, 1420, 200), 0.5);

	// MENU_SIGNUP : MENU DE CREATION DE COMPTE

	gui->textSignUp	= new_sprite_from_str("Creation d'un nouveau compte", 0, 0, 0);
	center_rect(gui->textSignUp->rect, new_rect(0, 150, 1920, 200), 1);

	gui->btnList[0] = gui->btnSolo;
	gui->btnList[1] = gui->btnMultiplayer;
	gui->btnList[2] = gui->btnArchives;
	gui->btnList[3] = gui->btnSettings;
	gui->btnList[4] = gui->btnQuit;
	gui->btnList[5] = gui->btnNext;
	gui->btnList[6] = gui->btnBack;
	gui->btnList[7] = gui->btnSignUp;
	// gui->btnList[8] = gui->btnLogin;

	gui->btnList[8] = gui->textboxUsername->box;
	gui->btnList[9] = gui->textboxPassword->box;

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

void draw_sprite(Sprite* sprite)
{
	SDL_RenderCopy(renderer, sprite->tex, sprite->texPos, sprite->rect);
}

void text_sprite_update(Sprite* sprite, char* text)
{
	SDL_Rect rect = *sprite->rect;
	Sprite* newSprite = new_sprite_from_str(text, 50, 0, 0);
	SDL_DestroyTexture(sprite->tex);
	sprite->tex = newSprite->tex;
	free(newSprite);
	SDL_QueryTexture(sprite->tex, NULL, NULL, &sprite->texPos->w, &sprite->texPos->h);
	sprite->rect->w = sprite->texPos->w * 0.5;
	sprite->rect->h = sprite->texPos->h * 0.5;
}

void textbox_update(Textbox *textbox)
{
	free(textbox->box->text);
	if (textbox->isPassword)
	{
		char hidedText[TEXTBOX_SIZE];
		for (int i = 0; i < textbox->textLen; i++) {
			hidedText[i] = '*';
		}
		hidedText[textbox->textLen] = '\0';
		textbox->box->text = new_sprite_from_str(hidedText, 255, 255, 255);
	}
	else
	{
		textbox->box->text = new_sprite_from_str(textbox->text, 255, 255, 255);
	}
	textbox->box->text->rect->x = textbox->box->bg->rect->x + 10;
	textbox->box->text->rect->w *= 0.5;
	textbox->box->text->rect->h *= 0.5;
	textbox->box->text->rect->y =  textbox->box->bg->rect->y + ( textbox->box->bg->rect->h/2 - textbox->box->text->rect->h/2);
	// center_rect(textbox->box->text->rect, textbox->box->bg->rect, 0.5);
}

void textbox_event(Textbox *textbox, SDL_Event event)
{
	int keycode = event.key.keysym.sym;

	if (keycode == SDLK_RETURN) //  || textbox->length >= TEXTBOX_SIZE
	{
		textbox->textLen = 0;
		printf("return0\n");
		return;
	}

	if (keycode == SDLK_BACKSPACE && textbox->textLen > 0)
	{
		textbox->textLen -= 1;
		textbox->text[textbox->textLen] = '\0';
		textbox_update(textbox);
		return;
	}
	else if ((keycode < 97 || keycode > 121) && keycode != SDLK_SPACE || textbox->textLen == TEXTBOX_SIZE - 1)
	{
		return;
	}
	SDL_Keymod mod = SDL_GetModState();
	if (((mod & KMOD_CAPS) || (mod & KMOD_SHIFT)) && keycode != SDLK_SPACE)
	{
		keycode -= 32;
	}
	textbox->text[textbox->textLen] = keycode;
	textbox->textLen += 1;
	textbox->text[textbox->textLen] = '\0';
	printf("keypress : %c    -    len : %d\n", keycode, textbox->textLen);
	textbox_update(textbox);
}


// DRAW MENU

void draw_main_menu(Gui* gui)
{
	SDL_SetRenderDrawColor(renderer, 0, 255, 100, 255);
	// SDL_RenderFillRect(renderer, gui->title->rect);
	draw_sprite(gui->title);
	draw_button(gui->btnSolo);
	draw_button(gui->btnMultiplayer);
	draw_button(gui->btnArchives);
	draw_button(gui->btnSettings);
	draw_button(gui->btnQuit);
}

void draw_login_menu(Gui* gui)
{

	draw_sprite(gui->textLogin);
	draw_sprite(gui->textUsername);
	draw_sprite(gui->textPassword);
	draw_button(gui->btnNext);
	draw_button(gui->btnSignUp);
	draw_button(gui->btnBack);
	draw_button(gui->textboxUsername->box);
	draw_button(gui->textboxPassword->box);
	draw_sprite(gui->textInfo);
}

void draw_signup_menu(Gui* gui)
{
	draw_sprite(gui->textSignUp);
	draw_sprite(gui->textUsername);
	draw_sprite(gui->textPassword);
	draw_button(gui->btnNext);
	draw_button(gui->btnBack);
	draw_button(gui->textboxUsername->box);
	draw_button(gui->textboxPassword->box);
	draw_sprite(gui->textInfo);
}
