// Tokaido by neigebaie (C) 2021
#include "utility.h"
#include "gui.h"
#include "board.h"

int main(int argc, const char *argv[])
{
	init();
	init_fps_counter();
	SDL_ShowCursor(0); // désactive le curseur windows pour afficher celui custom

	// load_textures();
	load_ressources();
	// create_main_menu();
	init_board();
	// Textures
	SDL_Point mousePos;

	SDL_Rect mouseRect = {0, 0, 0, 0};
	SDL_QueryTexture(gui.cursor, NULL, NULL, &mouseRect.w, &mouseRect.h);
	mouseRect.w /= 2;
	mouseRect.h /= 2;

	SDL_bool program_launched = SDL_TRUE;
	SDL_bool menu = SDL_TRUE;
	SDL_bool update = SDL_TRUE;
	int stage = 0;

	while (program_launched)
	{
		update_fps_counter();

		SDL_Event event;
		SDL_GetMouseState(&mousePos.x, &mousePos.y);
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_MOUSEMOTION:
					update = SDL_TRUE;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
						/*
						case SDLK_LEFT:
							gui.boardRect.x += 15;
							update = SDL_TRUE;
							break;
						case SDLK_RIGHT:
							gui.boardRect.x -= 15;
							update = SDL_TRUE;
							break;
						*/
						case SDLK_RETURN:
							// gui.partieTex = create_texture_from_str("Chargement des ressources...", 255, 200, 200);
							// gui.partieRect = centered_rect(gui.partieTex, gui.windowRect, 0.8);
							break;
						case SDLK_q:
						case SDLK_ESCAPE:
							program_launched = SDL_FALSE;
							break;
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						if (SDL_PointInRect(&mousePos, &gui.mMenuBtRect[0]))
						{
							printf("\e[31m [INFO] : Le bouton 0 a été cliqué ! ✨\n");
							menu = SDL_FALSE;
						}
						else if (SDL_PointInRect(&mousePos, &gui.mMenuBtRect[1]))
						{
							printf("\e[31m [INFO] : Le bouton 1 a été cliqué ! ✨\n");
						}
						else if (SDL_PointInRect(&mousePos, &gui.mMenuBtRect[2]))
						{
							printf("\e[31m [INFO] : Le bouton 2 a été cliqué ! ✨\n");
						}
						else if (SDL_PointInRect(&mousePos, &gui.mMenuBtRect[3]))
						{
							printf("\e[31m [INFO] : Le bouton 3 a été cliqué ! ✨\n");
						}
						else if (SDL_PointInRect(&mousePos, &gui.mMenuBtRect[4]))
						{
							program_launched = SDL_FALSE;
						}
					}
					break;
				case SDL_QUIT:
					program_launched = SDL_FALSE;
					break;
				default:
					break;
			}
		}

		if (menu)
		{

			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderClear(renderer);
			// draw_test();

			SDL_RenderCopy(renderer, gui.title, NULL, &gui.titleRect);

			for (int i = 0; i < 5; i++) {
				if (SDL_PointInRect(&mousePos, &gui.mMenuBtRect[i]))
					SDL_SetTextureColorMod(gui.button, 200, 200, 200);
				SDL_RenderCopy(renderer, gui.button, NULL, &gui.mMenuBtRect[i]);
				SDL_RenderCopy(renderer, gui.mMenuTex[i], NULL, &gui.mMenuTextRect[i]);
				SDL_SetTextureColorMod(gui.button, 255, 255, 255);
			}
			/*
			if (SDL_PointInRect(&mousePos, &gui.buttonRect))
				SDL_SetTextureColorMod(gui.button, 200, 200, 200);
			SDL_RenderCopy(renderer, gui.button, NULL, &gui.buttonRect);
			SDL_SetTextureColorMod(gui.button, 255, 255, 255);
			if (SDL_PointInRect(&mousePos, &gui.buttonRect1))
				SDL_SetTextureColorMod(gui.button, 200, 200, 200);
			SDL_RenderCopy(renderer, gui.button, NULL, &gui.buttonRect1);
			SDL_SetTextureColorMod(gui.button, 255, 255, 255);
			if (SDL_PointInRect(&mousePos, &gui.buttonRect2))
				SDL_SetTextureColorMod(gui.button, 200, 200, 200);
			SDL_RenderCopy(renderer, gui.button, NULL, &gui.buttonRect2);
			SDL_SetTextureColorMod(gui.button, 255, 255, 255);
			SDL_RenderCopy(renderer, gui.jouerTex, NULL, &gui.jouerRect);
			SDL_RenderCopy(renderer, gui.jouerOTex, NULL, &gui.jouerORect);
			SDL_RenderCopy(renderer, gui.quitTex, NULL, &gui.quitRect);
			*/
			// draw_squares(13);
			// update = SDL_FALSE;
		}
		else if (update)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderClear(renderer);
			// SDL_RenderCopy(renderer, gui.board, NULL, &gui.boardRect);
			// update = SDL_FALSE;
		}

		mouseRect.x = mousePos.x;
		mouseRect.y = mousePos.y;
		SDL_RenderCopy(renderer, gui.cursor, NULL, &mouseRect); // cursor toujours au dessus

		SDL_RenderPresent(renderer);
		// SDL_Delay(11);
	}

	exit_with_success();
	return EXIT_SUCCESS;
}
