// Tokaido by neigebaie (C) 2021
#include "utility.h"
#include "gui.h"
#include "board.h"
#include "input.h"

int main(int argc, const char *argv[])
{
	init();
	init_fps_counter();
	SDL_ShowCursor(0); // désactive le curseur windows pour afficher celui custom

	// load_textures();
	load_ressources();
	// save_ressources("ressources.dat");
	create_main_menu();
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

	SDL_bool saisie = SDL_FALSE;

	Textbox* textbox = init_textbox();

	int stage = 0;
	int scroll = 0;
	unsigned int frameLimit = SDL_GetTicks() + FPS_LIMIT;

	while (program_launched)
	{
		update_fps_counter();

		SDL_Event event;
		SDL_GetMouseState(&mousePos.x, &mousePos.y);
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_KEYUP:
					switch (event.key.keysym.sym)
					{
						case SDLK_LEFT:
							scroll = 0;
							break;
						case SDLK_RIGHT:
							scroll = 0;
							break;
					}
					break;
				case SDL_KEYDOWN:
					if (saisie) {
						input_str(event, textbox);
						textbox->texture = create_texture_from_str(textbox->text, 0, 13, 0);
						textbox->rect = centered_rect(textbox->texture, gui.titleRect, 1);
						debug_textbox(textbox);
						if (!textbox->length)
							saisie = SDL_FALSE;
						break;
					}
					switch (event.key.keysym.sym)
					{
						case SDLK_RETURN:
							if (!menu)
								random_move();
							else
								reset_textbox(textbox);
								debug_textbox(textbox);
								saisie = SDL_TRUE;
							break;
						case SDLK_LEFT:
							scroll = 1;
							break;
						case SDLK_RIGHT:
							scroll = -1;
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
							printf("\e[31m [INFO] : Le bouton Solo a été cliqué ! ✨\e[37m\n");
							menu = SDL_FALSE;
						}
						else if (SDL_PointInRect(&mousePos, &gui.mMenuBtRect[1]))
						{
							printf("\e[32m [INFO] : Le bouton Multi a été cliqué ! ✨\e[37m\n");
						}
						else if (SDL_PointInRect(&mousePos, &gui.mMenuBtRect[2]))
						{
							printf("\e[33m [INFO] : Le bouton Archives a été cliqué ! ✨\e[37m\n");
						}
						else if (SDL_PointInRect(&mousePos, &gui.mMenuBtRect[3]))
						{
							printf("\e[34m [INFO] : Le bouton Options a été cliqué ! ✨\e[37m\n");
						}
						else if (SDL_PointInRect(&mousePos, &gui.mMenuBtRect[4]))
						{
							printf("\e[35m [INFO] : Le bouton Quitter a été cliqué ! ✨\e[37m\n");
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

		board.camera.origin += scroll * 10;


		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		// draw_board();
		// draw_test();
		if (menu)
		{
			// SDL_RenderCopy(renderer, gui.title, NULL, &gui.titleRect);
			SDL_RenderCopy(renderer, textbox->texture, NULL, &textbox->rect);
			for (int i = 0; i < 5; i++) {
				if (SDL_PointInRect(&mousePos, &gui.mMenuBtRect[i]))
					SDL_SetTextureColorMod(gui.button, 200, 200, 200);
				SDL_RenderCopy(renderer, gui.button, NULL, &gui.mMenuBtRect[i]);
				SDL_RenderCopy(renderer, gui.mMenuTex[i], NULL, &gui.mMenuTextRect[i]);
				SDL_SetTextureColorMod(gui.button, 255, 255, 255);
			}
		}
		else
		{
			draw_board();
		}

		mouseRect.x = mousePos.x;
		mouseRect.y = mousePos.y;
		SDL_RenderCopy(renderer, gui.cursor, NULL, &mouseRect); // cursor toujours au dessus

		SDL_RenderPresent(renderer);
		frameLimit = SDL_GetTicks() + FPS_LIMIT;
		limit_fps(frameLimit);
	}

	exit_with_success();
	return EXIT_SUCCESS;
}
