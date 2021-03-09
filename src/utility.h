#ifndef UTILITY_H_
#define UTILITY_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH 	1920
#define WINDOW_HEIGHT 1080

extern SDL_Window 	*window;
extern SDL_Renderer *renderer;
extern TTF_Font			*font;

void init(void);
void exit_with_success(void);
void exit_with_error(const char *message);
#endif
