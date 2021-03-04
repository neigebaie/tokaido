#include "helper.h"
#define OFFSET 150

void button()
{
	init();
	int ww = 640;
	int wh = 480;

	// create and load surface
	SDL_Surface *tempSurface = NULL;
	tempSurface = IMG_Load("gfx/button.png");

	// create and define texture
	SDL_Texture *Texture = NULL;
	Texture = SDL_CreateTextureFromSurface(Renderer, tempSurface);

	tempSurface = IMG_Load("gfx/panorama1.png");

	SDL_Texture *Panorama = NULL;
	Panorama = SDL_CreateTextureFromSurface(Renderer, tempSurface);
	//clean temp surface
	SDL_FreeSurface(tempSurface);

	// get texture dimensions
	int tw, th;
	SDL_QueryTexture(Texture, NULL, NULL, &tw, &th);

	// scale texture size down
	 tw /= 3;
	 th /= 3;
	//	set button destination rect centered on screen
	//x		    y		    w	h
	SDL_Rect Texture_dst_rect = {ww / 2 - tw / 2, 100, tw, th};

	SDL_QueryTexture(Panorama, NULL, NULL, &tw, &th);

	printf("%d : %d : %d\n", tw, th, (int)((float)th * ((float)ww/(float)tw)));
	SDL_Rect Panorama_src_rect = {1024, 0, 1024, 395};
	SDL_Rect Panorama_dst_rect = {0, 0, ww, (int)((float)Panorama_src_rect.h * ((float)ww/(float)Panorama_src_rect.w))};

	int origin = Texture_dst_rect.y;
	SDL_SetWindowSize(Window, ww, wh);
	SDL_SetWindowPosition(Window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	SDL_SetWindowTitle(Window, "Tokaido");
	SDL_ShowWindow(Window);

	TTF_Init();
	TTF_Font *font;
	SDL_Color textColor = { 255, 255, 255, 255 };
	font = TTF_OpenFont("fonts/Buried K9.ttf", 40);
	if (font == NULL)
		printf("ERROR\n");

	SDL_Surface *message = NULL;
	message = TTF_RenderText_Blended(font, "Commencer une partie", textColor);
	SDL_Texture *Message = NULL;
	Message = SDL_CreateTextureFromSurface(Renderer, message);
	SDL_QueryTexture(Message, NULL, NULL, &tw, &th);
	SDL_Rect Message_dst_rect = {ww / 2 - tw / 2, 130, tw, th};
	int origin_m = Message_dst_rect.y;

	SDL_bool background_color_flipped = SDL_FALSE;
	SDL_Point mouse_coords;
	SDL_Event event;
	int running = 1;

	while (running)
	{
		SDL_GetMouseState(&mouse_coords.x, &mouse_coords.y);
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = 0;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					if (SDL_PointInRect(&mouse_coords, &Texture_dst_rect))
					{
						printf("\e[31m [INFO] : Le bouton a été cliqué ! ✨\n");
						if (background_color_flipped)
						{
							background_color_flipped = SDL_FALSE;
							Message_dst_rect.y = origin_m;
							Texture_dst_rect.y = origin;
						}
						else
						{
							background_color_flipped = SDL_TRUE;
							Message_dst_rect.y = origin_m + 10;
							Texture_dst_rect.y = origin + 10;
						}
					}
				}
				if (event.button.button == SDL_BUTTON_RIGHT)
				{
					;
				}
			}
		}

		if (SDL_PointInRect(&mouse_coords, &Texture_dst_rect))
		{
			Message_dst_rect.y = origin_m + 5;
			Texture_dst_rect.y = origin + 5;
		}
		else
		{
			Message_dst_rect.y = origin_m;
			Texture_dst_rect.y = origin;
		}

		SDL_SetRenderDrawColor(Renderer, 255, 251, 247, 255);
		SDL_RenderClear(Renderer);

		SDL_RenderCopy(Renderer, Panorama, &Panorama_src_rect, &Panorama_dst_rect);
		for (int i = 0; i < 3; i++) {
			SDL_Rect Texture_dst_rect_i = {Texture_dst_rect.x, Texture_dst_rect.y + i * OFFSET, Texture_dst_rect.w, Texture_dst_rect.h};
			SDL_Rect Message_dst_rect_i = {Message_dst_rect.x, Message_dst_rect.y + i * OFFSET, Message_dst_rect.w, Message_dst_rect.h};
			SDL_RenderCopy(Renderer, Texture, NULL, &Texture_dst_rect_i);
			SDL_RenderCopy(Renderer, Message, NULL, &Message_dst_rect_i);
		}

		// apply_surface( 0, 200, message, screen );

		// SDL_SetRenderDrawColor(Renderer, r, 0, 0, 255);
		// SDL_RenderDrawRect(Renderer, &Texture_dst_rect);
		SDL_RenderPresent(Renderer);
	}
	SDL_DestroyTexture(Texture);
	TTF_CloseFont(font);
	exit_();
}
