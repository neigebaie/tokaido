#ifndef INPUT_H_
#define INPUT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

#define TEXT_SIZE 64

typedef struct {
	SDL_Texture *texture;
	SDL_Rect rect;
	char* text;
	SDL_bool caps;
	int length;
} Textbox;

void input_str(SDL_Event event, Textbox *textbox);
Textbox* init_textbox(void);
void reset_textbox(Textbox *textbox);
void debug_textbox(Textbox *textbox);

#endif
