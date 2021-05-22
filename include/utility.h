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

typedef enum
{
	STATE_IDLE,
	STATE_HOVERED,
	STATE_CLICKED,
	STATE_DISABLED
} State;

typedef enum
{
	AT_TOP_LEFT,
	AT_TOP_CENTER,
	AT_BOTTOM_LEFT,
	AT_BOTTOM_RIGHT,
	AT_CENTER
} At;

typedef struct {
	int x, y;
} Offset;

typedef struct {
	int w, h;
} Size;

typedef struct
{
	At at;
	Offset offset;
	Size size;
} AnchorInfo;

typedef struct
{
		SDL_Texture* tex;
		SDL_Rect* crop;
		AnchorInfo* parent;
		AnchorInfo ai;
} Sprite;

typedef struct
{
	// All the textures in the game
	SDL_Texture* bgTex[10];
	SDL_Texture* squareTex;
	SDL_Texture* foodTex;
	SDL_Texture* travelerTex;
	SDL_Texture* itemTex;
	SDL_Texture* encounterTex;
	SDL_Texture* lbIcontex;
	SDL_Texture* iconTex;
	SDL_Texture* guiTex;

	Sprite bg[10];
	Sprite title;
	Sprite button;
	Sprite textbox;
	Sprite bundleTkIcon;
	Sprite coinIcon;
	Sprite itemCatIcons[4];
	Sprite lbIcons[9];
	Sprite templeCoinIcon;
	Sprite frame;

} TextureMgr;

extern SDL_Window*   window;
extern SDL_Renderer* renderer;
extern TTF_Font*     font;
extern TextureMgr*   textureMgr;
extern AnchorInfo    windowAnchor;

extern SDL_bool program_launched;
extern double clickedUntil;

extern int k, debugMode, fps;

void init(void);

void shuffle(int *array, size_t n);
float min(float f1, float f2);

void limit_fps(unsigned int limit);
void init_fps_counter();
void update_fps_counter();

void show_splash_screen();

SDL_Texture* load_texture(const char *path);
void load_textures();
void destroy_textures();

SDL_Rect anchored_rect(AnchorInfo ai, AnchorInfo* parentAi);
SDL_bool is_ai_on_screen(AnchorInfo* ai);
void log_player(int value, int newline);

Sprite* new_sprite(SDL_Texture* tex, SDL_Rect* crop);

SDL_Rect* new_rect(int x, int y, int w, int h);
SDL_bool is_rect_on_screen(SDL_Rect* rect);
void print_rect(SDL_Rect* rect);
void print_ai(AnchorInfo* ai);

void state_color_mod(SDL_Texture* tex, State* state);

void exit_with_success(void);
void exit_with_error(const char *message);

#endif
