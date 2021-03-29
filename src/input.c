#include "input.h"

void input_str(SDL_Event event, Textbox *textbox)
{
	int keycode = event.key.keysym.sym;

	if (keycode == SDLK_RETURN || textbox->length >= TEXT_SIZE)
		textbox->length = 0;
		return;

	if (keycode < 97 || keycode > 121)
		return;

	textbox->text[textbox->length] = keycode;
	textbox->length = 1;
	textbox->text[textbox->length] = '\0';
}

Textbox* init_textbox()
{
	Textbox* textbox;
	printf("init\n");
	sprintf(textbox->text, "<Saisie>");
	textbox->length = 0;
	textbox->texture = NULL;
	textbox->rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	textbox->rect->x = 0;
	textbox->rect->y = 0;
	textbox->rect->w = 0;
	textbox->rect->h = 0;
	textbox->caps = SDL_FALSE;
	return textbox;
}

void debug_textbox(Textbox* textbox)
{
	printf("%s\n", textbox->text);
	printf("%d\n", textbox->length);
	// textbox->texture = NULL;
	printf("%d\n", textbox->rect->x);
	printf("%d\n", textbox->rect->y);
	printf("%d\n", textbox->rect->w);
	printf("%d\n", textbox->rect->h);
	// textbox->caps = SDL_FALSE;
}
