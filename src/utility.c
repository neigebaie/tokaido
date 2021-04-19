#include "utility.h"

// Argh, global variables...
SDL_Window   	*window    = NULL;
SDL_Renderer 	*renderer  = NULL;
TTF_Font 			*font      = NULL;

char title[100];
int freq;
int curr_count;
int last_count;
float delta_time;
float update_time;
float time_passed;
int fps;

void init(void)
{
	// Initialisation SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		exit_with_error("Initialisation SDL échouée");

	// Création de la fenêtre (SDL_Window)
	window = SDL_CreateWindow(
		"Tokaido",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_FULLSCREEN // SDL_WINDOW_SHOWN : pour la version fenêtrée
	);

	if (window == NULL)
		exit_with_error("Création de la fenêtre échouée");

	// Chargement de l'icon
	SDL_Surface *icon = NULL;
	icon = IMG_Load("ressources/gfx/gui/icon.png");
	SDL_SetWindowIcon(window, icon);
	SDL_FreeSurface(icon);

	// Création du renderer (SDL_Renderer)
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // | SDL_RENDERER_PRESENTVSYNC

	if (renderer == NULL)
		exit_with_error("Création du Renderer échouée");

	// Initialisation SDL_TTF
	TTF_Init();
	font = TTF_OpenFont("ressources/fonts/Buried K9.ttf", 80);
	if (font == NULL)
		exit_with_error("\ressources/fonts/Buried K9.ttf\" n'a pas pu être chargé");
}

void shuffle(int *array, size_t n)
{
    if (n > 1)
    {
        size_t i;
        for (i = 0; i < n - 1; i++)
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

void init_fps_counter()
{
    curr_count = SDL_GetPerformanceCounter();
    last_count = 0;
    update_time = 0;
}

void update_fps_counter()
{
    last_count = curr_count;
    curr_count = SDL_GetPerformanceCounter();
    freq = SDL_GetPerformanceFrequency();
    delta_time = (float)(curr_count - last_count) / (float)freq;
    fps = (int)(1.f / delta_time);
    update_time += delta_time;

    if (update_time >= 1.f)
		{
        time_passed += update_time;
        sprintf(title, "Tokaido by neigebaie      Time:  %.2f  -  FPS:  %d", time_passed, fps);
        SDL_SetWindowTitle(window, title);
        update_time -= 1.f;
    }
}

void limit_fps(unsigned int limit)
{
    unsigned int ticks = SDL_GetTicks();
		if (limit < ticks)
			return;
		else if (limit > ticks + (1000/FPS_LIMIT))
			SDL_Delay((1000/FPS_LIMIT));
		else
			SDL_Delay(limit - ticks);
}

SDL_Texture * load_texture(const char *path)
{
	SDL_Surface *surface = NULL;
	SDL_Texture *texture = NULL;
	surface = IMG_Load(path);
	if (surface == NULL)
		exit_with_error("Création de surface échouée");
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL)
		exit_with_error("Création de texture échouée");
	SDL_FreeSurface(surface);
	return texture;
}

Sprite* new_sprite(SDL_Texture* tex, SDL_Rect* texPos)
{
	Sprite* sprite = (Sprite*)malloc(sizeof(Sprite));
	sprite->tex = tex;
	sprite->texPos = texPos;
	sprite->rect = new_rect(0, 0, texPos->w, texPos->h);
	return sprite;
}

SDL_Rect* new_rect(int x, int y, int w, int h)
{
	SDL_Rect* rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
	return rect;
}

SDL_bool is_rect_on_screen(SDL_Rect* rect)
{
	if (
		(
			(rect->x >= 0 && rect->x <= WINDOW_WIDTH) ||
			(rect->x + rect->w >= 0 && rect->x + rect->w <= WINDOW_WIDTH)
		)
		&&
		(
			(rect->y >= 0 && rect->y <= WINDOW_HEIGHT) ||
			(rect->y + rect->h >= 0 && rect->y + rect->h <= WINDOW_HEIGHT)
		)
	)
	{
		return SDL_TRUE;
	}
	else
	{
		return SDL_FALSE;
	}
}

void exit_with_error(const char *message)
{
	// Affiche un message d'erreur et quitte le programme
	printf("\e[31m ERREUR 🥺 : %s > %s\e[37m\n", message, SDL_GetError());
	exit(EXIT_FAILURE);
}

void exit_with_success(void)
{
	// Nettoyage à la sortie du programme
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
	// printf("\e[34m Au revoir !\e[37m\n"); // debug
}
