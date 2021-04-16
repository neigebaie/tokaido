// Tokaido by QINTO Esteban & SERANDER Paul (C) 2021
#include "utility.h"
#include "gui.h"
#include "game.h"
#include "board.h"
#include "account.h"

#define MENU_MAIN     0
#define MENU_LOGIN    1
#define MENU_SIGNUP   2
#define MENU_ARCHIVES 3
#define MENU_SETTINGS 4
#define MENU_BOARD    5

int main(int argc, const char *argv[])
{
	init();
	init_fps_counter();
	// SDL_ShowCursor(0); // désactive le curseur windows pour afficher celui custom
	// SDL_SetCursor(init_system_cursor(arrow));

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
	SDL_bool menu = MENU_MAIN;
	SDL_bool update = SDL_TRUE;

	Textbox* focusedTextbox = NULL;

	int stage = 0;
	int scroll = 0;
	unsigned int frameLimit = SDL_GetTicks() + FPS_LIMIT;

	while (program_launched)
	{
		update_fps_counter();

		SDL_Event event;
		SDL_GetMouseState(&mousePos.x, &mousePos.y);

		for (int btnId = 0; btnId < BTN_NB; btnId++) {
			if (SDL_PointInRect(&mousePos, gui->btnList[btnId]->bg->rect))
			{
				gui->btnList[btnId]->hovered = SDL_TRUE;
			} else {
				gui->btnList[btnId]->hovered = SDL_FALSE;
			}
			if (gui->btnList[btnId]->clicked) {
				gui->btnList[btnId]->clicked -= 1;
			}
		}

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
					if (focusedTextbox) {
						textbox_event(focusedTextbox, event);
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
								// reset_textbox(textbox);
								focusedTextbox = gui->textboxUsername;
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
						for (int btnId = 0; btnId < BTN_NB; btnId++) {
							if (SDL_PointInRect(&mousePos, gui->btnList[btnId]->bg->rect))
							{
								gui->btnList[btnId]->clicked = 10;
								// gui->btnSolo->action();
							}
						}
						switch (menu)
						{
							case MENU_MAIN:
								if (SDL_PointInRect(&mousePos, gui->btnSolo->bg->rect))
								{
									printf("\e[31m [INFO] : Le bouton Solo a été cliqué ! ✨\e[37m\n");
									menu = MENU_BOARD;
								}
								else if (SDL_PointInRect(&mousePos, gui->btnMultiplayer->bg->rect))
								{
									printf("\e[32m [INFO] : Le bouton Multi a été cliqué ! ✨\e[37m\n");
									menu = MENU_LOGIN;
								}
								else if (SDL_PointInRect(&mousePos, gui->btnArchives->bg->rect))
								{
									printf("\e[33m [INFO] : Le bouton Archives a été cliqué ! ✨\e[37m\n");
									menu = MENU_SIGNUP;
								}
								else if (SDL_PointInRect(&mousePos, gui->btnSettings->bg->rect))
								{
									printf("\e[34m [INFO] : Le bouton Options a été cliqué ! ✨\e[37m\n");
								}
								else if (SDL_PointInRect(&mousePos, gui->btnQuit->bg->rect))
								{
									printf("\e[35m [INFO] : Le bouton Quitter a été cliqué ! ✨\e[37m\n");
									program_launched = SDL_FALSE;
								}
								break;
							case MENU_LOGIN:
							focusedTextbox = NULL;
								if (SDL_PointInRect(&mousePos, gui->btnSignUp->bg->rect))
								{
									printf("\e[31m [INFO] : Le bouton SignUp a été cliqué ! ✨\e[37m\n");
									menu = MENU_SIGNUP;
									strcpy(gui->textInfoStr, "");
									text_sprite_update(gui->textInfo, gui->textInfoStr);
								}
								else if (SDL_PointInRect(&mousePos, gui->btnNext->bg->rect))
								{
									printf("\e[32m [INFO] : Le bouton Next a été cliqué ! ✨\e[37m\n");
									if (account_login(gui->textboxUsername->text, gui->textboxPassword->text, gui->textInfoStr))
									{
										printf("Connexion échouée !\n");
									}
									else
									{
										printf("Connexion réussie !\n");
										gui->textboxUsername->text[0] = 0;
										gui->textboxUsername->textLen = 0;
										textbox_update(gui->textboxUsername);
									}
									focusedTextbox = NULL;
									gui->textboxPassword->text[0] = 0;
									gui->textboxPassword->textLen = 0;
									textbox_update(gui->textboxPassword);
									text_sprite_update(gui->textInfo, gui->textInfoStr);
								}
								else if (SDL_PointInRect(&mousePos, gui->btnBack->bg->rect))
								{
									printf("\e[33m [INFO] : Le bouton Back a été cliqué ! ✨\e[37m\n");
									menu = MENU_MAIN;
									strcpy(gui->textInfoStr, "");
									text_sprite_update(gui->textInfo, gui->textInfoStr);
								}
								else if (SDL_PointInRect(&mousePos, gui->textboxUsername->box->bg->rect))
								{
									focusedTextbox = gui->textboxUsername;
								}
								else if (SDL_PointInRect(&mousePos, gui->textboxPassword->box->bg->rect))
								{
									focusedTextbox = gui->textboxPassword;
								}
								break;
							case MENU_SIGNUP:
								if (SDL_PointInRect(&mousePos, gui->btnNext->bg->rect))
								{
									printf("\e[32m [INFO] : Le bouton Next a été cliqué ! ✨\e[37m\n");
									if (account_create(gui->textboxUsername->text, gui->textboxPassword->text, gui->textInfoStr))
									{
										printf("Création échouée !\n");
									}
									else
									{
										printf("Compte créé !\n");
										gui->textboxUsername->text[0] = 0;
										gui->textboxUsername->textLen = 0;
										textbox_update(gui->textboxUsername);
									}
									focusedTextbox = NULL;
									gui->textboxPassword->text[0] = 0;
									gui->textboxPassword->textLen = 0;
									textbox_update(gui->textboxPassword);
									text_sprite_update(gui->textInfo, gui->textInfoStr);
								}
								else if (SDL_PointInRect(&mousePos, gui->btnBack->bg->rect))
								{
									printf("\e[33m [INFO] : Le bouton Back a été cliqué ! ✨\e[37m\n");
									menu = MENU_LOGIN;
									strcpy(gui->textInfoStr, "");
									text_sprite_update(gui->textInfo, gui->textInfoStr);
								}
								else if (SDL_PointInRect(&mousePos, gui->textboxUsername->box->bg->rect))
								{
									focusedTextbox = gui->textboxUsername;
								}
								else if (SDL_PointInRect(&mousePos, gui->textboxPassword->box->bg->rect))
								{
									focusedTextbox = gui->textboxPassword;
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

		// UPDATE MGR
		board.camera.origin += scroll * 10;
		if (menu == MENU_BOARD)
			; // update_board();

		// RENDER MGR
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
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
			case MENU_SIGNUP:
				draw_signup_menu(gui);
				break;
		}

		// mouseRect.x = mousePos.x;
		// mouseRect.y = mousePos.y;
		// SDL_RenderCopy(renderer, gui->cursor->tex, gui->cursor->texPos, &mouseRect); // cursor toujours au dessus

		SDL_RenderPresent(renderer);

		// FPS MGR
		frameLimit = SDL_GetTicks() + FPS_LIMIT;
		limit_fps(frameLimit);
	}

	exit_with_success();
	return EXIT_SUCCESS;
}
