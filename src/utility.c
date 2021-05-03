#include <utility.h>

SDL_Window*   window    = NULL;
SDL_Renderer* renderer  = NULL;
TTF_Font*     font      = NULL;
TextureMgr*   textureMgr = NULL;
SDL_bool program_launched = SDL_TRUE;
int debugMode = 0;
int k = 0;

double clickedUntil = 0;

char title[100];
int freq;
int curr_count;
int last_count;
float delta_time;
float update_time;
float time_passed;
int fps;

AnchorInfo windowAnchor;

void init(void)
{
	// Initialisation SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		exit_with_error("Initialisation SDL échouée");

	// Création de la fenêtre (SDL_Window)
	window = SDL_CreateWindow(
		"Tokaido",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1280, 720,
		SDL_WINDOW_SHOWN // SDL_WINDOW_SHOWN : pour la version fenêtrée
		 // SDL_WINDOW_FULLSCREEN|SDL_WINDOW_BORDERLESS
	);

	if (window == NULL)
		exit_with_error("Création de la fenêtre échouée");

	SDL_GetWindowSize(window, &windowAnchor.size.w, &windowAnchor.size.h);

	// Chargement de l'icon
	SDL_Surface *icon = NULL;
	icon = IMG_Load("resources/gfx/gui/icon.png");
	SDL_SetWindowIcon(window, icon);
	SDL_FreeSurface(icon);

	// Création du renderer (SDL_Renderer)
	// renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == NULL)
		exit_with_error("Création du Renderer échouée");

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	// SDL_setenv("SDL_VIDEODRIVER", "directx", 1);
	// SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2"); // Add option in settings

	// Initialisation SDL_TTF
	TTF_Init();
	font = TTF_OpenFont("resources/fonts/Buried K9.ttf", 80);
	if (font == NULL)
		exit_with_error("\"resources/fonts/Buried K9.ttf\" n'a pas pu être chargé");
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

float min(float f1, float f2)
{
	if (f1 < f2)
		return f1;
	else
		return f2;
}

// FPS
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
        sprintf(title, "Tokaido by neigebaie      UpdateT:  %d  -  FPS:  %d", (int)(curr_count - last_count)/1000, fps);
        SDL_SetWindowTitle(window, title);
        update_time -= 1.f;
    }
}

void show_splash_screen()
{
	SDL_Texture* splashScreenTex = load_texture("resources/gfx/bg/splash.png");
	SDL_RenderCopy(renderer, splashScreenTex, NULL, NULL);
	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(splashScreenTex);
}

// TEXTURES
SDL_Texture* load_texture(const char *path)
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

void load_textures()
{
	textureMgr = (TextureMgr*)malloc(sizeof(TextureMgr));
	// TEXTURES

	textureMgr->bgTex[0]        = load_texture("resources/gfx/bg/menu_main.png");
	textureMgr->bgTex[1]        = load_texture("resources/gfx/bg/pan_rice.png");
	textureMgr->bgTex[2]        = load_texture("resources/gfx/bg/pan_mount.png");
	textureMgr->bgTex[3]        = load_texture("resources/gfx/bg/pan_sea.png");
	textureMgr->bgTex[4]        = load_texture("resources/gfx/bg/shop_inn.png");

	textureMgr->squareTex       = load_texture("resources/gfx/square_spritesheet.png");
	textureMgr->foodTex         = load_texture("resources/gfx/food_spritesheet.png");
	textureMgr->travelerTex     = load_texture("resources/gfx/traveler_spritesheet.png");
	textureMgr->itemTex         = load_texture("resources/gfx/item_spritesheet.png");
	// textureMgr->encounterTex   = load_texture("resources/gfx/encounter_spritesheet.png");
	textureMgr->iconTex         = load_texture("resources/gfx/gui/icon_spritesheet.png");
	textureMgr->guiTex          = load_texture("resources/gfx/gui/gui_spritesheet.png");

	textureMgr->title   = *new_sprite(textureMgr->guiTex, new_rect(0, 308, 888, 335));

	textureMgr->button  = *new_sprite(textureMgr->guiTex, new_rect(0, 0, 1319, 307));
	textureMgr->button.ai.size.w *= 0.3;
	textureMgr->button.ai.size.h *= 0.3;

	textureMgr->textbox = *new_sprite(textureMgr->guiTex, new_rect(0, 647, 1319, 307));
	textureMgr->textbox.ai.size.w *= 0.5;
	textureMgr->textbox.ai.size.h *= 0.3;

	textureMgr->bg[0]        = *new_sprite(textureMgr->bgTex[0], new_rect(0, 0, 1920, 1080));
	textureMgr->bg[1]        = *new_sprite(textureMgr->bgTex[1], new_rect(0, 0, 1920, 1080));
	textureMgr->bg[2]        = *new_sprite(textureMgr->bgTex[2], new_rect(0, 0, 1920, 1080));
	textureMgr->bg[3]        = *new_sprite(textureMgr->bgTex[3], new_rect(0, 0, 1920, 1080));
	textureMgr->bg[4]        = *new_sprite(textureMgr->bgTex[4], new_rect(0, 0, 1920, 1080));

	textureMgr->bundleTkIcon = *new_sprite(textureMgr->iconTex, new_rect(256, 0, 256, 256));
	textureMgr->bundleTkIcon.ai.size.w = 40;
	textureMgr->bundleTkIcon.ai.size.h = 40;

	textureMgr->coinIcon = *new_sprite(textureMgr->iconTex, new_rect(0, 0, 256, 256));
	textureMgr->coinIcon.ai.size.w = 40;
	textureMgr->coinIcon.ai.size.h = 40;

	for (int i = 0; i < 4 /*ITEM_CATS*/; i++) {
		textureMgr->itemCatIcons[i] = *new_sprite(textureMgr->iconTex, new_rect(128 * i, 384, 128, 128));
		textureMgr->itemCatIcons[i].ai.size.w = 40;
		textureMgr->itemCatIcons[i].ai.size.h = 40;
	}

	textureMgr->templeCoinIcon = *new_sprite(textureMgr->iconTex, new_rect(0, 256, 128, 128));
	textureMgr->templeCoinIcon.ai.size.w = 40;
	textureMgr->templeCoinIcon.ai.size.h = 40;

	textureMgr->frame = *new_sprite(textureMgr->guiTex, new_rect(1320, 0, 643, 882));
	textureMgr->frame.ai.size.w = 200;
	textureMgr->frame.ai.size.h = 300;

	printf("\e[32m [DEBUG] Textures loaded !\e[37m\n");
}

void destroy_textures()
{
	SDL_DestroyTexture(textureMgr->squareTex);
	SDL_DestroyTexture(textureMgr->foodTex);
	SDL_DestroyTexture(textureMgr->travelerTex);
	SDL_DestroyTexture(textureMgr->itemTex);
	// SDL_DestroyTexture(textureMgr->encounterTex);
	SDL_DestroyTexture(textureMgr->iconTex);
	SDL_DestroyTexture(textureMgr->guiTex);
	SDL_DestroyTexture(textureMgr->bgTex[0]);
	SDL_DestroyTexture(textureMgr->bgTex[1]);
	SDL_DestroyTexture(textureMgr->bgTex[2]);
	SDL_DestroyTexture(textureMgr->bgTex[3]);
	SDL_DestroyTexture(textureMgr->bgTex[4]);
}

Sprite* new_sprite(SDL_Texture* tex, SDL_Rect* crop)
{
	Sprite* sprite = (Sprite*)malloc(sizeof(Sprite));

	sprite->tex = tex;

	sprite->crop = crop;

	sprite->parent = NULL;

	sprite->ai.at = AT_TOP_LEFT;

	sprite->ai.offset.x = 0;
	sprite->ai.offset.y = 0;

	sprite->ai.size.w = crop->w;
	sprite->ai.size.h = crop->h;

	return sprite;
}

// ANCHOR
SDL_Rect anchored_rect(AnchorInfo ai, AnchorInfo* parentAi)
{
	SDL_Rect rect;
	SDL_Rect parent;
	if (parentAi != NULL)
	{
		parent = anchored_rect(*parentAi, NULL);
		// print_rect(&parent);
	}
	else
	{
		parent.x = 0;
		parent.y = 0;
		parent.w = windowAnchor.size.w;
		parent.h = windowAnchor.size.h;
	}
	float scale = min((float)windowAnchor.size.w / 1920, (float)windowAnchor.size.h / 1080);
	rect.w = ai.size.w * scale;
	rect.h = ai.size.h * scale;

	switch (ai.at)
	{
		case AT_CENTER:
			rect.x = parent.w / 2 - rect.w / 2;
			rect.y = parent.h / 2 - rect.h / 2;
			break;
		case AT_TOP_CENTER:
			rect.x = parent.w / 2 - rect.w / 2;
			rect.y = 0;
			break;
		case AT_TOP_LEFT:
			rect.x = 0;
			rect.y = 0;
			break;
		case AT_BOTTOM_LEFT:
			rect.x = 0;
			rect.y = parent.h - rect.h;
			break;
		case AT_BOTTOM_RIGHT:
			rect.x = parent.w - rect.w;
			rect.y = parent.h - rect.h;
			break;
	}

	rect.x += parent.x + ai.offset.x  * scale;
	rect.y += parent.y + ai.offset.y  * scale;

	return rect;
}

// RECT
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
	return 1;
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	SDL_Rect screenRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
	// SDL_RenderDrawRect(renderer, &screenRect);
	if (
		(
			(rect->x >= screenRect.x && rect->x <= screenRect.x + screenRect.w) ||
			(rect->x + rect->w >= screenRect.x && rect->x + rect->w <= screenRect.x + screenRect.w)
		)
		&&
		(
			(rect->y >= screenRect.y && rect->y <= screenRect.y + screenRect.h) ||
			(rect->y + rect->h >= screenRect.y && rect->y + rect->h <= screenRect.y + screenRect.h)
		)
	)
	{
		k++;
		return SDL_TRUE;
	}
	else
	{
		return SDL_FALSE;
	}
}

void print_rect(SDL_Rect* rect)
{
	printf("[Rect] %4d %4d %4d %4d\n", rect->x, rect->y, rect->w, rect->h);
}

void print_ai(AnchorInfo* ai)
{
	if (ai == NULL)
		printf("[DEBUG] NULL\n");
	else
		printf("[DEBUG] %d : %d %d %d %d\n", ai->at, ai->offset.x, ai->offset.y, ai->size.w, ai->size.h);
}

void state_color_mod(SDL_Texture* tex, State* state)
{
	switch (*state) {
		case STATE_IDLE:
			break;
		case STATE_CLICKED:
			if (!clickedUntil)
				clickedUntil = SDL_GetTicks() + 100;
			SDL_SetTextureColorMod(tex, 200, 200, 200);
			break;
		case STATE_HOVERED:
			SDL_SetTextureColorMod(tex, 220, 220, 220);
			break;
		case STATE_DISABLED:
			SDL_SetTextureColorMod(tex, 120, 100, 100);
			break;
	}
}

// EXIT
void exit_with_error(const char *message)
{
	// Affiche un message d'erreur et quitte le programme
	printf("\e[31m ERREUR 🥺 : %s > %s\e[37m\n", message, SDL_GetError());
	exit(EXIT_FAILURE);
}

void exit_with_success(void)
{
	// Nettoyage à la sortie du programme
	destroy_textures();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
	// printf("\e[34m Au revoir !\e[37m\n"); // debug
}
