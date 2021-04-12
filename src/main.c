// Tokaido by QINTO Esteban & SERANDER Paul (C) 2021
#include "utility.h"
#include "gui.h"
#include "game.h"
#include "board.h"
#include "input.h"

#define MENU_MAIN     0
#define MENU_LOGIN    1
#define MENU_SETTINGS 2
#define MENU_BOARD    3

int main(int argc, const char *argv[])
{
	init();
	init_fps_counter();
	// SDL_ShowCursor(0); // désactive le curseur windows pour afficher celui custom

	// load_textures();
	load_ressources();
	Gui* gui = gui_init();
	init_board();
	// Textures
	SDL_Point mousePos;

	SDL_Rect mouseRect = {0, 0, 0, 0};
	mouseRect.w = gui->cursor->rect->w;
	mouseRect.h = gui->cursor->rect->h;

	SDL_bool program_launched = SDL_TRUE;
	SDL_bool menu = MENU_BOARD;
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
						textbox->rect = centered_rect(textbox->texture, gui->title->rect, 1);
						if (!textbox->length)
							saisie = SDL_FALSE;
						break;
					}
					switch (event.key.keysym.sym)
					{
						case SDLK_RETURN:
							if (menu == MENU_BOARD)
							{
								random_move();
							}
							else
							{
								reset_textbox(textbox);
								saisie = SDL_TRUE;
							}
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
						switch (menu)
						{
							case MENU_MAIN:
								if (SDL_PointInRect(&mousePos, gui->btnSolo->rect))
								{
									printf("\e[31m [INFO] : Le bouton Solo a été cliqué ! ✨\e[37m\n");
									menu = MENU_BOARD;
								}
								else if (SDL_PointInRect(&mousePos, gui->btnMultiplayer->rect))
								{
									printf("\e[32m [INFO] : Le bouton Multi a été cliqué ! ✨\e[37m\n");
								}
								else if (SDL_PointInRect(&mousePos, gui->btnArchives->rect))
								{
									printf("\e[33m [INFO] : Le bouton Archives a été cliqué ! ✨\e[37m\n");
								}
								else if (SDL_PointInRect(&mousePos, gui->btnSettings->rect))
								{
									printf("\e[34m [INFO] : Le bouton Options a été cliqué ! ✨\e[37m\n");
								}
								else if (SDL_PointInRect(&mousePos, gui->btnQuit->rect))
								{
									printf("\e[35m [INFO] : Le bouton Quitter a été cliqué ! ✨\e[37m\n");
									program_launched = SDL_FALSE;
								}
								break;
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
		switch (menu)
		{
			case MENU_MAIN:
				draw_main_menu(gui);
				break;
			case MENU_BOARD:
				draw_board();
				break;
			case MENU_LOGIN:
				draw_login_menu(gui);
				break;
		}

		mouseRect.x = mousePos.x;
		mouseRect.y = mousePos.y;
		SDL_RenderCopy(renderer, gui->cursor->atlas, gui->cursor->atlasPos, &mouseRect); // cursor toujours au dessus

		SDL_RenderPresent(renderer);
		frameLimit = SDL_GetTicks() + FPS_LIMIT;
		limit_fps(frameLimit);
	}

	exit_with_success();
	return EXIT_SUCCESS;
}
