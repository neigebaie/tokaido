#include "input.h"

void input_str(SDL_Event event, Textbox *textbox)
{
	int keycode = event.key.keysym.sym;
	printf("keypress : %c \n", keycode);


	if (keycode == SDLK_RETURN) //  || textbox->length >= TEXT_SIZE
	{
		textbox->length = 0;
		printf("return0\n");
		return;
	}

	if (keycode == SDLK_BACKSPACE)
	{
		textbox->length -= 1;
		textbox->text[textbox->length] = '\0';
		return;
	}
	else if ((keycode < 97 || keycode > 121) && keycode != SDLK_SPACE )
	{
		printf("return1\n");
		return;
	}
	SDL_Keymod mod = SDL_GetModState();
	if (((mod & KMOD_CAPS) || (mod & KMOD_SHIFT)) && keycode != SDLK_SPACE)
	{
		keycode -= 32;
	}
	printf("len : %d\n", textbox->length);
	textbox->text[textbox->length] = keycode;
	textbox->length += 1;
	textbox->text[textbox->length] = '\0';

	// debug_textbox(textbox);
	// printf("\n");
}

Textbox* init_textbox()
{
	Textbox* textbox = (Textbox*)malloc(sizeof(Textbox));
	textbox->text = (char*)malloc(sizeof(char) * TEXT_SIZE);
	textbox->length = 0;
	textbox->sprite = new_sprite(NULL, new_rect(0, 0, 0, 0));
	textbox->rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	textbox->rect->x = 0;
	textbox->rect->y = 0;
	textbox->rect->w = 0;
	textbox->rect->h = 0;
	textbox->caps = SDL_FALSE;
	return textbox;
}

void reset_textbox(Textbox* textbox)
{
	printf("reset\n");
	sprintf(textbox->text, "");
	textbox->length = 0;
	textbox->sprite->tex = NULL;
	textbox->rect->x = 0;
	textbox->rect->y = 0;
	textbox->rect->w = 0;
	textbox->rect->h = 0;
	textbox->caps = SDL_FALSE;
}
