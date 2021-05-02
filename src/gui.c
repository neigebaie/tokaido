#include <gui.h>

Gui* init_gui()
{
	Gui* gui = (Gui*)malloc(sizeof(Gui));

	gui->mainMenu     = new_main_menu();
	gui->loginMenu    = new_login_menu();
	gui->signupMenu   = new_signup_menu();
	gui->archivesMenu = new_archives_menu();
	gui->settingsMenu = new_settings_menu();

	gui->menus[MENU_MAIN] = gui->mainMenu;
	gui->menus[MENU_LOGIN] = gui->loginMenu;
	gui->menus[MENU_SIGNUP] = gui->signupMenu;
	gui->menus[MENU_ARCHIVES] = gui->archivesMenu;
	gui->menus[MENU_SETTINGS] = gui->settingsMenu;

	printf("\e[32m [DEBUG] Gui initialized !\e[37m\n");
	return gui;
}

// MENU
Menu* base_menu(int s, int t, int tb, int b)
{
	Menu* menu = (Menu*)malloc(sizeof(Menu));

	menu->spriteCount = s;
	menu->textCount = t;
	menu->textboxCount = tb;
	menu->buttonCount = b;
	menu->sprites = (Sprite**)malloc(sizeof(Sprite*) * menu->spriteCount);
	menu->texts = (Text**)malloc(sizeof(Text*) * menu->textCount);
	menu->textboxes = (Textbox**)malloc(sizeof(Textbox*) * menu->textboxCount);
	menu->buttons = (Button**)malloc(sizeof(Button*) * menu->buttonCount);

	return menu;
}

Menu* new_main_menu(Gui* gui)
{
	Menu* menu = base_menu(2, 1, 0, 5);
	int y = -350;

	menu->sprites[0] = &textureMgr->bg[0];
	menu->sprites[0]->ai.at = AT_CENTER;

	menu->sprites[1] = &textureMgr->title;
	menu->sprites[1]->ai.at = AT_CENTER;
	menu->sprites[1]->ai.offset.y = y;
	y += menu->sprites[1]->ai.size.h;

	menu->texts[0] = new_text("Tokaido v0.2.0", 100, 100, 100, 0.35);
	menu->texts[0]->sprite->ai.offset = (Offset){10, 10};
	menu->texts[0]->sprite->ai.at = AT_BOTTOM_LEFT;

	menu->buttons[0] = new_button("Solo",        0.5, ACTION_START_SOLO, MENU_BOARD);
	menu->buttons[1] = new_button("Multijoueur", 0.5, ACTION_START_LAN,  MENU_NONE);
	menu->buttons[2] = new_button("Archives",    0.5, ACTION_NONE,       MENU_ARCHIVES);
	menu->buttons[3] = new_button("Options",     0.5, ACTION_NONE,       MENU_SETTINGS);
	menu->buttons[4] = new_button("Quitter",     0.5, ACTION_QUIT,       MENU_NONE);

	for (int i = 0; i < menu->buttonCount; i++)
	{
		menu->buttons[i]->bg.ai.at = AT_CENTER;
		menu->buttons[i]->bg.ai.offset.y = y;
		y += menu->buttons[i]->bg.ai.size.h + 30;
	}

	return menu;
}

Menu* new_login_menu()
{
	Menu* menu = base_menu(0, 3, 2, 3);

	menu->texts[0] = new_text("Connexion", 0, 0, 0, 1);
	menu->texts[0]->sprite->ai.offset = (Offset){0, 10};
	menu->texts[0]->sprite->ai.at = AT_TOP_CENTER;

	menu->texts[1] = new_text("Nom d'utilisateur", 0, 0, 0, 0.5);
	menu->texts[1]->sprite->ai.offset = (Offset){-300, -200};
	menu->texts[1]->sprite->ai.at = AT_CENTER;

	menu->texts[2] = new_text("Mot de passe", 0, 0, 0, 0.5);
	menu->texts[2]->sprite->ai.offset = (Offset){-300, -100};
	menu->texts[2]->sprite->ai.at = AT_CENTER;

	menu->textboxes[0] = new_textbox(SDL_FALSE, 1);
	menu->textboxes[0]->bg.ai.offset = (Offset){150, -200};
	menu->textboxes[0]->bg.ai.at = AT_CENTER;

	menu->textboxes[1] = new_textbox(SDL_TRUE, 0);
	menu->textboxes[1]->bg.ai.offset = (Offset){150, -100};
	menu->textboxes[1]->bg.ai.at = AT_CENTER;


	menu->buttons[0] = new_button("Suivant",         0.5, ACTION_LOGIN,  MENU_NONE);
	menu->buttons[1] = new_button("Créer un compte", 0.5, ACTION_NONE,   MENU_SIGNUP);
	menu->buttons[2] = new_button("Retour",          0.5, ACTION_NONE,   MENU_MAIN);

	int y = 100;
	for (int i = 0; i < menu->buttonCount; i++)
	{
		menu->buttons[i]->bg.ai.at = AT_CENTER;
		menu->buttons[i]->bg.ai.offset.y = y;
		y += menu->buttons[i]->bg.ai.size.h + 30;
	}

	return menu;
}

Menu* new_signup_menu()
{
	Menu* menu = base_menu(0, 3, 2, 2);

	menu->texts[0] = new_text("Création d'un compte", 0, 0, 0, 1);
	menu->texts[0]->sprite->ai.offset = (Offset){0, 10};
	menu->texts[0]->sprite->ai.at = AT_TOP_CENTER;

	menu->texts[1] = new_text("Nom d'utilisateur", 0, 0, 0, 0.5);
	menu->texts[1]->sprite->ai.offset = (Offset){-300, -200};
	menu->texts[1]->sprite->ai.at = AT_CENTER;

	menu->texts[2] = new_text("Mot de passe", 0, 0, 0, 0.5);
	menu->texts[2]->sprite->ai.offset = (Offset){-300, -100};
	menu->texts[2]->sprite->ai.at = AT_CENTER;

	menu->textboxes[0] = new_textbox(SDL_FALSE, 1);
	menu->textboxes[0]->bg.ai.offset = (Offset){150, -200};
	menu->textboxes[0]->bg.ai.at = AT_CENTER;

	menu->textboxes[1] = new_textbox(SDL_TRUE, 0);
	menu->textboxes[1]->bg.ai.offset = (Offset){150, -100};
	menu->textboxes[1]->bg.ai.at = AT_CENTER;


	menu->buttons[0] = new_button("Suivant", 0.5, ACTION_SIGNUP, MENU_NONE);
	menu->buttons[1] = new_button("Retour",  0.5, ACTION_NONE,   MENU_LOGIN);

	int y = 100;
	for (int i = 0; i < menu->buttonCount; i++)
	{
		menu->buttons[i]->bg.ai.at = AT_CENTER;
		menu->buttons[i]->bg.ai.offset.y = y;
		y += menu->buttons[i]->bg.ai.size.h + 30;
	}

	return menu;
}

Menu* new_archives_menu()
{
	Menu* menu = base_menu(0, 1, 0, 1);

	menu->texts[0] = new_text("Archives", 0, 0, 0, 1);
	menu->texts[0]->sprite->ai.offset = (Offset){0, 10};
	menu->texts[0]->sprite->ai.at = AT_TOP_CENTER;

	menu->buttons[0] = new_button("Retour",  0.5, ACTION_NONE,   MENU_MAIN);

	int y = 100;
	for (int i = 0; i < menu->buttonCount; i++)
	{
		menu->buttons[i]->bg.ai.at = AT_CENTER;
		menu->buttons[i]->bg.ai.offset.y = y;
		y += menu->buttons[i]->bg.ai.size.h + 30;
	}

	return menu;
}

Menu* new_settings_menu()
{
	Menu* menu = base_menu(0, 1, 0, 1);

	menu->texts[0] = new_text("Options", 0, 0, 0, 1);
	menu->texts[0]->sprite->ai.offset = (Offset){0, 10};
	menu->texts[0]->sprite->ai.at = AT_TOP_CENTER;

	menu->buttons[0] = new_button("Retour",  0.5, ACTION_NONE,   MENU_MAIN);

	int y = 100;
	for (int i = 0; i < menu->buttonCount; i++)
	{
		menu->buttons[i]->bg.ai.at = AT_CENTER;
		menu->buttons[i]->bg.ai.offset.y = y;
		y += menu->buttons[i]->bg.ai.size.h + 30;
	}

	return menu;
}

void draw_menu(Menu* menu)
{
	// bg or decorative sprites
	for (int i = 0; i < menu->spriteCount; i++)
	{
		draw_sprite(menu->sprites[i]);
	}

	// texts
	for (int i = 0; i < menu->textCount; i++)
	{
		draw_sprite(menu->texts[i]->sprite);
	}

	// input fields
	for (int i = 0; i < menu->textboxCount; i++)
	{
		draw_textbox(menu->textboxes[i]);
	}

	// buttons to interact with
	for (int i = 0; i < menu->buttonCount; i++)
	{
		draw_button(menu->buttons[i]);
	}
	// printf("\n\n");
}

void update_menu(Menu* menu); // :thinking: Hmmm...

void destroy_menu(Menu* menu)
{
	free(menu);
}

// SPRITE
void draw_sprite(Sprite* sprite)
{
	SDL_Rect rect = anchored_rect(sprite->ai, sprite->parent);
	if (is_rect_on_screen(&rect))
		SDL_RenderCopy(renderer, sprite->tex, sprite->crop, &rect);
	if (debugMode)
	{
		SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
		SDL_RenderDrawRect(renderer, &rect);
	}
}

// BUTTON
Button* new_button(char* content, float scale, Action action, MenuId nextMenuId)
{
	Button* button = (Button*)malloc(sizeof(Button));

	button->bg = textureMgr->button;
	button->text = new_text(content, 255, 255, 255, scale);
	button->text->sprite->ai.at = AT_CENTER;
	button->text->sprite->parent = &button->bg.ai;
	button->state = STATE_IDLE;
	button->action = action;
	button->nextMenuId = nextMenuId;

	return button;
}

void draw_button(Button* button)
{
	state_color_mod(button->bg.tex, &button->state);
	draw_sprite(&button->bg);
	SDL_SetTextureColorMod(button->bg.tex, 255, 255, 255);
	draw_sprite(button->text->sprite);
}

void button_action(Button* button, MenuId* menuId)
{
	printf("\e[33m [INFO] : Le bouton %s a été cliqué ! ✨\e[37m\n", button->text->content);

	switch (button->action)
	{
		case ACTION_NONE:
			break;
		case ACTION_QUIT:
			program_launched = SDL_FALSE;
			break;
		case ACTION_START_SOLO:
			break;
		case ACTION_START_LAN:
			break;
		case ACTION_LOGIN:
			break;
		case ACTION_SIGNUP:
			break;
		case ACTION_JOIN_LAN:
			break;
		case ACTION_TEMPLE:
			break;
		case ACTION_BUY:
			break;
		case ACTION_END_TURN:
			end_turn();
			break;
	}

	if (button->nextMenuId != MENU_NONE)
		*menuId = button->nextMenuId;
}

void destroy_button(Button* button)
{
	free(button);
}

// TEXT
Text* new_text(char* content, int r, int g, int b, float scale)
{
	Text* text = (Text*)malloc(sizeof(Text));
	SDL_Color color = {r, g, b};

	text->sprite = (Sprite*)malloc(sizeof(Sprite));
	text->sprite->tex = NULL;
	text->sprite->crop = NULL;
	text->sprite->parent = NULL;
	text->sprite->ai.offset.x = 0;
	text->sprite->ai.offset.y = 0;
	text->sprite->ai.at = AT_TOP_LEFT;


	strcpy(text->content, content);
	text->color = color;
	text->scale = scale;
	update_text(text);

	return text;
}

void update_text(Text* text)
{
	SDL_Surface *surface = NULL;
	SDL_Texture *texture = NULL;

	if (text->sprite->tex != NULL)
		SDL_DestroyTexture(text->sprite->tex);

	surface = TTF_RenderUTF8_Blended(font, text->content, text->color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	Sprite* sprite = new_sprite(texture, new_rect(0, 0, 0, 0));
	SDL_QueryTexture(sprite->tex, NULL, NULL, &sprite->crop->w, &sprite->crop->h);
	sprite->parent = text->sprite->parent;
	sprite->ai = text->sprite->ai;
	sprite->ai.size.w = sprite->crop->w * text->scale;
	sprite->ai.size.h = sprite->crop->h * text->scale;

	text->sprite = sprite;
}

void destroy_text(Text* text)
{
	SDL_DestroyTexture(text->sprite->tex);
	free(text);
}

// TEXTBOX
Textbox* new_textbox(SDL_bool isPassword, int nextTextboxId)
{
	Textbox* textbox = (Textbox*)malloc(sizeof(Textbox));
	textbox->bg = textureMgr->textbox;

	textbox->text = new_text("", 255, 255, 255, 0.5);
	textbox->text->sprite->ai.offset = (Offset){10, 10};
	textbox->text->sprite->ai.at = AT_TOP_LEFT;
	textbox->text->sprite->parent = &textbox->bg.ai;

	textbox->textLen = 0;
	textbox->state = STATE_IDLE;
	textbox->isPassword = isPassword;
	textbox->nextTextboxId = nextTextboxId;

	return textbox;
}

void textbox_event(Textbox *textbox, SDL_Event* event)
{
	char keycode = event->key.keysym.sym;
	char passwordBuffer[TEXT_LEN];

	if (keycode == SDLK_RETURN)
	{
		// unfocus textbox
	}
	else if (keycode == SDLK_TAB)
	{
		// focus on next textbox
	}
	else if (keycode == SDLK_BACKSPACE && textbox->textLen > 0)
	{
		textbox->textLen -= 1;
		textbox->text->content[textbox->textLen] = '\0';
	}
	else
	{

		if (((keycode < 97 || keycode > 121) && keycode != SDLK_SPACE) || textbox->textLen == TEXT_LEN - 1)
		{
			return;
		}
		SDL_Keymod mod = SDL_GetModState();
		if (((mod & KMOD_CAPS) || (mod & KMOD_SHIFT)) && keycode != SDLK_SPACE)
		{
			keycode -= 32;
		}

		textbox->text->content[textbox->textLen] = keycode;
		textbox->textLen++;
		textbox->text->content[textbox->textLen] = '\0';
	}

	if (textbox->isPassword)
	{
		strcpy(passwordBuffer, textbox->text->content);
		for (int i = 0; i < textbox->textLen; i++)
		{
			textbox->text->content[i] = '*';
		}
		textbox->text->content[textbox->textLen] = '\0';
	}
	update_text(textbox->text);
	if (textbox->isPassword)
		strcpy(textbox->text->content, passwordBuffer);
}

void draw_textbox(Textbox* textbox)
{
	state_color_mod(textbox->bg.tex, &textbox->state);
	draw_sprite(&textbox->bg);
	SDL_SetTextureColorMod(textbox->bg.tex, 255, 255, 255);
	draw_sprite(textbox->text->sprite);
}

void destroy_textbox(Textbox* textbox)
{
	destroy_text(textbox->text);
	free(textbox);
}
