#ifndef UTILITY_H_
#define UTILITY_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH 	1920
#define WINDOW_HEIGHT 1080
#define FPS_LIMIT 60


typedef struct {
		SDL_Texture* tex; // spritesheet/texture
		SDL_Rect* texPos; // position in the spritesheet (px) (NULL if texture)
		SDL_Rect* rect;   // where to draw it onscreen
} Sprite;

extern SDL_Window 	*window;
extern SDL_Renderer *renderer;
extern TTF_Font			*font;

void init(void);

void shuffle(int *array, size_t n);

void limit_fps(unsigned int limit);
void init_fps_counter();
void update_fps_counter();

SDL_Texture* load_texture(const char *path);

Sprite* new_sprite(SDL_Texture* tex, SDL_Rect* texPos);
SDL_Rect* new_rect(int x, int y, int w, int h);

SDL_bool is_rect_on_screen(SDL_Rect* rect);

void exit_with_success(void);
void exit_with_error(const char *message);

#endif
