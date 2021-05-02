// Tokaido by QUINTO Esteban & SERANDER Paul (C) 2021
#include <utility.h>
#include <gui.h>
#include <time.h>
#include <stdlib.h>
#include <game.h>
#include <board.h>
#include <account.h>

void debug_aff(int debugMode, Text* debugText, double time_spent);

int frameCount = 0;

int main(int argc, const char *argv[])
{
	double startedAt = SDL_GetTicks();
	init();
	init_fps_counter();
	show_splash_screen();
	// SDL_SetCursor(init_system_cursor(arrow));
	Account* loggedAccount = guest_account();
	SDL_bool logged = SDL_TRUE; // SDL_FALSE debug

	load_textures();
	load_resources();

	Gui* gui = init_gui();
	MenuId menuId = MENU_MAIN;
	Menu* menu = gui->menus[menuId];
	if (logged) // à décaler évidemment
		init_board(loggedAccount, textureMgr);

	SDL_Point mousePos;

	Textbox* focusedTextbox = NULL;
	Button* clickedButton = NULL;

	// debug
	k = 0; // debug
	Text* debugText = new_text("Loading debug info...", 255, 255, 255, 0.45);
	debugText->sprite->ai.at = AT_BOTTOM_LEFT;
	debugText->sprite->ai.offset.x = 10;
	debugText->sprite->ai.offset.y = 10;

	while (SDL_GetTicks() - startedAt < 500)
	{
		SDL_Delay(100);
	}

	while (program_launched)
	{
		update_fps_counter();
		clock_t begin = clock();

		SDL_Event event;
		SDL_GetMouseState(&mousePos.x, &mousePos.y);

		if (menuId != MENU_BOARD)
		{
			for (int btnId = 0; btnId < menu->buttonCount; btnId++)
			{
				if (menu->buttons[btnId]->state != STATE_CLICKED)
				{
					SDL_Rect rect = anchored_rect(menu->buttons[btnId]->bg.ai, menu->buttons[btnId]->bg.parent);
					if (SDL_PointInRect(&mousePos, &rect))
					{
						menu->buttons[btnId]->state = STATE_HOVERED;
					}
					else
					{
						menu->buttons[btnId]->state = STATE_IDLE;
					}
				}
			}
			for (int id = 0; id < menu->textboxCount; id++)
			{
				if (menu->textboxes[id]->state != STATE_CLICKED)
				{
					SDL_Rect rect = anchored_rect(menu->textboxes[id]->bg.ai, menu->textboxes[id]->bg.parent);
					if (SDL_PointInRect(&mousePos, &rect))
					{
						menu->textboxes[id]->state = STATE_HOVERED;
					}
					else
					{
						menu->textboxes[id]->state = STATE_IDLE;
					}
				}
			}
		}

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_KEYDOWN:
					if (focusedTextbox)
					{
						textbox_event(focusedTextbox, &event);
						printf("textbox_event\n");
						break;
					}
					switch (event.key.keysym.sym)
					{
						case SDLK_F1:
							k -= 1;
							break;
						case SDLK_F2:
							k += 1;
							break;
						case SDLK_F12:
							debugMode = (debugMode + 1) % 4;
							break;
						case SDLK_ESCAPE:
							if (menuId == MENU_MAIN)
								program_launched = SDL_FALSE;
							else
							{
								menu = gui->mainMenu;
								menuId = MENU_MAIN;
							}
							break;
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						if (menuId != MENU_BOARD)
						{
							focusedTextbox = NULL;
							for (int btnId = 0; btnId < menu->buttonCount; btnId++)
							{
								SDL_Rect rect = anchored_rect(menu->buttons[btnId]->bg.ai, menu->buttons[btnId]->bg.parent);
								if (SDL_PointInRect(&mousePos, &rect))
								{
									menu->buttons[btnId]->state = STATE_CLICKED;
									clickedButton = menu->buttons[btnId];
								}
							}
							for (int id = 0; id < menu->textboxCount; id++)
							{
								SDL_Rect rect = anchored_rect(menu->textboxes[id]->bg.ai, menu->textboxes[id]->bg.parent);
								if (SDL_PointInRect(&mousePos, &rect))
								{
									menu->textboxes[id]->state = STATE_CLICKED;
									focusedTextbox = menu->textboxes[id];
									printf("new focusedTextbox\n");
								}
							}
						}
					}
					break;
				case SDL_WINDOWEVENT:
					SDL_GetWindowSize(window, &windowAnchor.size.w, &windowAnchor.size.h);
					break;

				// case SDL_MOUSEBUTTONDOWN:
				// 	if (event.button.button == SDL_BUTTON_LEFT)
				// 	{
				// 		for (int btnId = 0; btnId < BTN_NB; btnId++)
				// 		{
				// 			if (SDL_PointInRect(&mousePos, gui->btnList[btnId]->bg->rect))
				// 			{
				// 				; // gui->btnList[btnId]->clicked = 1;
				// 			}
				// 		}
				// 		switch (menu)
				// 		{
				// 			case MENU_LOGIN:
				// 			focusedTextbox = NULL;
				// 				if (SDL_PointInRect(&mousePos, gui->btnSignUp->bg->rect))
				// 				{
				// 					printf("\e[31m [INFO] : Le bouton SignUp a été cliqué ! ✨\e[37m\n");
				// 					menu = MENU_SIGNUP;
				// 					text_info_clear(gui->textInfo);
				// 				}
				// 				else if (SDL_PointInRect(&mousePos, gui->btnNext->bg->rect))
				// 				{
				// 					printf("\e[32m [INFO] : Le bouton Next a été cliqué ! ✨\e[37m\n");
				// 					if (account_login(loggedAccount, gui->textboxUsername->text, gui->textboxPassword->text, gui->textInfo->text))
				// 					{
				// 						printf("Connexion échouée !\n");
				// 					}
				// 					else
				// 					{
				// 						logged = SDL_TRUE;
				// 						printf("Connexion réussie ! %s\n", loggedAccount->nick);
				// 						gui->textboxUsername->text[0] = 0;
				// 						gui->textboxUsername->textLen = 0;
				// 						textbox_update(gui->textboxUsername);
				// 					}
				// 					focusedTextbox = NULL;
				// 					gui->textboxPassword->text[0] = 0;
				// 					gui->textboxPassword->textLen = 0;
				// 					textbox_update(gui->textboxPassword);
				// 					text_info_update(gui->textInfo);
				// 				}
				// 				else if (SDL_PointInRect(&mousePos, gui->btnBack->bg->rect))
				// 				{
				// 					printf("\e[33m [INFO] : Le bouton Back a été cliqué ! ✨\e[37m\n");
				// 					menu = MENU_MAIN;
				// 					text_info_clear(gui->textInfo);
				// 				}
				// 				else if (SDL_PointInRect(&mousePos, gui->textboxUsername->box->bg->rect))
				// 				{
				// 					focusedTextbox = gui->textboxUsername;
				// 				}
				// 				else if (SDL_PointInRect(&mousePos, gui->textboxPassword->box->bg->rect))
				// 				{
				// 					focusedTextbox = gui->textboxPassword;
				// 				}
				// 				break;
				// 			case MENU_SIGNUP:
				// 				if (SDL_PointInRect(&mousePos, gui->btnNext->bg->rect))
				// 				{
				// 					printf("\e[32m [INFO] : Le bouton Next a été cliqué ! ✨\e[37m\n");
				// 					if (account_create(gui->textboxUsername->text, gui->textboxPassword->text, gui->textInfo->text))
				// 					{
				// 						printf("Création échouée !\n");
				// 					}
				// 					else
				// 					{
				// 						printf("Compte créé !\n");
				// 						gui->textboxUsername->text[0] = 0;
				// 						gui->textboxUsername->textLen = 0;
				// 						textbox_update(gui->textboxUsername);
				// 					}
				// 					focusedTextbox = NULL;
				// 					gui->textboxPassword->text[0] = 0;
				// 					gui->textboxPassword->textLen = 0;
				// 					textbox_update(gui->textboxPassword);
				// 					text_info_update(gui->textInfo);
				// 				}
				// 				else if (SDL_PointInRect(&mousePos, gui->btnBack->bg->rect))
				// 				{
				// 					printf("\e[33m [INFO] : Le bouton Back a été cliqué ! ✨\e[37m\n");
				// 					menu = MENU_LOGIN;
				// 					text_info_clear(gui->textInfo);
				// 				}
				// 				else if (SDL_PointInRect(&mousePos, gui->textboxUsername->box->bg->rect))
				// 				{
				// 					focusedTextbox = gui->textboxUsername;
				// 				}
				// 				else if (SDL_PointInRect(&mousePos, gui->textboxPassword->box->bg->rect))
				// 				{
				// 					focusedTextbox = gui->textboxPassword;
				// 				}
				// 				break;
				// 		}
				// 	}
				// 	break;
				case SDL_QUIT:
					program_launched = SDL_FALSE;
					break;
			}
			if (menuId == MENU_BOARD)
			{
				board_event(&event, &mousePos);
			}
		}

		if (SDL_GetTicks() > clickedUntil && clickedUntil && clickedButton != NULL)
		{
			button_action(clickedButton, &menuId);
			clickedButton->state = STATE_IDLE;
			clickedButton = NULL;
			clickedUntil = 0;
		}

		// RENDER MGR
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
		SDL_RenderClear(renderer);
		k = 0;

		if (menuId == MENU_BOARD)
		{
			if (!is_game_started())
			{
				begin_turn();
			}
			board_update();
			draw_board();
		}
		else
		{
			draw_menu(menu);
			menu = gui->menus[menuId];
		}

		clock_t end = clock();
		double time_spent = (1000 * (double)(end - begin) / CLOCKS_PER_SEC);
		frameCount++;

		debug_aff(debugMode, debugText, time_spent);

		SDL_RenderPresent(renderer);
	}

	exit_with_success();
	return EXIT_SUCCESS;
}

void debug_aff(int debugMode, Text* debugText, double time_spent)
{
	SDL_Rect rect;
	switch (debugMode)
	{
		case 3:
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			for (int i = 0; i < windowAnchor.size.w; i += windowAnchor.size.w / 10)
			{
				SDL_RenderDrawLine(renderer, i, 0, i, windowAnchor.size.h);
			}
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			for (int i = 0; i < windowAnchor.size.h; i += windowAnchor.size.h / 10)
			{
				SDL_RenderDrawLine(renderer, 0, i, windowAnchor.size.w, i);
			}

		case 2:
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

			rect.w = 1;
			rect.h = windowAnchor.size.h;
			rect.x = windowAnchor.size.w / 2 - rect.w / 2;
			rect.y = windowAnchor.size.h / 2 - rect.h / 2;
			SDL_RenderFillRect(renderer, &rect);

			rect.w = windowAnchor.size.w;
			rect.h = 1;
			rect.x = windowAnchor.size.w / 2 - rect.w / 2;
			rect.y = windowAnchor.size.h / 2 - rect.h / 2;
			SDL_RenderFillRect(renderer, &rect);

		case 1:
			if (frameCount % 50 == 0)
			{
				sprintf(debugText->content, "  time elapsed (ms) = %.2lf   debug int k = %d  FPS = %d  ", time_spent, k, fps);
				frameCount = 0;
			}

			update_text(debugText);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 105);
			SDL_Rect rect = anchored_rect(debugText->sprite->ai, debugText->sprite->parent);
			SDL_RenderFillRect(renderer, &rect);

			draw_sprite(debugText->sprite);
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

			rect.w = 20;
			rect.h = 4;
			rect.x = windowAnchor.size.w / 2 - rect.w / 2;
			rect.y = windowAnchor.size.h / 2 - rect.h / 2;
			SDL_RenderFillRect(renderer, &rect);

			rect.w = 4;
			rect.h = 20;
			rect.x = windowAnchor.size.w / 2 - rect.w / 2;
			rect.y = windowAnchor.size.h / 2 - rect.h / 2;
			SDL_RenderFillRect(renderer, &rect);

			SDL_SetRenderDrawColor(renderer, 50, 100, 50, 255);

			rect.w = 18;
			rect.h = 2;
			rect.x = windowAnchor.size.w / 2 - rect.w / 2;
			rect.y = windowAnchor.size.h / 2 - rect.h / 2;
			SDL_RenderFillRect(renderer, &rect);

			rect.w = 2;
			rect.h = 18;
			rect.x = windowAnchor.size.w / 2 - rect.w / 2;
			rect.y = windowAnchor.size.h / 2 - rect.h / 2;
			SDL_RenderFillRect(renderer, &rect);
			break;
		default:
		break;
	}
}
