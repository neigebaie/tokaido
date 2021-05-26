#ifndef UTILITY_H_
#define UTILITY_H_

#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

// écran de réf
#define WINDOW_WIDTH 	1920
#define WINDOW_HEIGHT 1080
// fps cap
#define FPS_LIMIT 60

// État d'un élément graphique, utilisé par les boutons entre autres
typedef enum
{
	STATE_IDLE,
	STATE_HOVERED,
	STATE_CLICKED,
	STATE_DISABLED
} State;

// Points d'ancrage, pour les coordonnées relatives des sprites
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

// Structure contenant les caractéristiques d'un sprite
typedef struct
{
	At at;
	Offset offset;
	Size size;
} AnchorInfo;

// sprite, structure universelle dans le programme qui permet la
// gestion de spritesheet ainisi que les pts d'ancrage
typedef struct
{
		SDL_Texture* tex;
		SDL_Rect* crop;
		AnchorInfo* parent; // un sprite peut être centré sur un autre
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

// variables globales
extern SDL_Window*   window;
extern SDL_Renderer* renderer;
extern TTF_Font*     font;
extern TextureMgr*   textureMgr;
extern AnchorInfo    windowAnchor;

extern SDL_bool program_launched;
extern double clickedUntil;

extern int k, debugMode, fps;

// initialisation SDL (renderer, window, SDL_image, SDL_ttf)
void init(void);

// mélange une array
void shuffle(int *array, size_t n);
float min(float f1, float f2);

// limite et infos sur les FPS
void limit_fps(unsigned int limit);
void init_fps_counter();
void update_fps_counter();

// écran de chargement au lancement du jeu
void show_splash_screen();

// permet de charger une texture depuis son emplacement
SDL_Texture* load_texture(const char *path);
void load_textures();
void destroy_textures(); // libère les textures à la sortie du programme

// permet de transformer une information de pt d'ancrage en coordonnées de pixels sur l'écran
SDL_Rect anchored_rect(AnchorInfo ai, AnchorInfo* parentAi);
SDL_bool is_ai_on_screen(AnchorInfo* ai); // pour économiser des ressources
// void log_player(int value, int newline);

Sprite* new_sprite(SDL_Texture* tex, SDL_Rect* crop);

SDL_Rect* new_rect(int x, int y, int w, int h);
SDL_bool is_rect_on_screen(SDL_Rect* rect); // pour économiser des ressources
void print_rect(SDL_Rect* rect); // debug
void print_ai(AnchorInfo* ai); // debug

// applique une couleur à une texture en fonction d'un état d'élément graphique
void state_color_mod(SDL_Texture* tex, State* state);

void exit_with_success(void);
void exit_with_error(const char *message);

#endif
