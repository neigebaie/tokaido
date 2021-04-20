// Tokaido by QUINTO Esteban & SERANDER Paul (C) 2021
#include <utility.h>
#include <gui.h>
#include <game.h>
#include <board.h>
#include <account.h>

#define MENU_MAIN      0
#define MENU_LOGIN     1
#define MENU_SIGNUP    2
#define MENU_ACCOUNT   3
#define MENU_LOAD      4
#define MENU_SAVE      5
#define MENU_CHAR_SEL  6
#define MENU_RULES     7
#define MENU_ARCHIVES  8
#define MENU_SETTINGS  9
#define MENU_BOARD    10

int frameCount = 0;

int main(int argc, const char *argv[])
{
	init();
	init_fps_counter();
	// SDL_SetCursor(init_system_cursor(arrow));
	Account* loggedAccount = (Account*)malloc(sizeof(Account));
	// SDL_bool logged = SDL_FALSE;
	SDL_bool logged = SDL_TRUE; // debug

	TextureMgr* textureMgr = load_textures();
	load_ressources(textureMgr);

	Gui* gui = gui_init(textureMgr);

	SDL_Point mousePos;

	SDL_bool program_launched = SDL_TRUE;
	int menu = MENU_MAIN;

	Textbox* focusedTextbox = NULL;

	// debug
	int debugMode = 0;
	float k = 20;
	SDL_Rect rect;
	TextInfo* debugInfo = new_text_info(0, 0, 0, 1);
	debugInfo->sprite->rect->x = 10;
	debugInfo->sprite->rect->y = 10;

	SDL_Point scroll = {0, 0};
	float zoom = 0.f;
	unsigned int frameLimit = SDL_GetTicks() + (1000 / FPS_LIMIT);

	while (program_launched)
	{
		clock_t begin = clock();
		update_fps_counter();

		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_MOUSEMOTION:
					SDL_GetMouseState(&mousePos.x, &mousePos.y);

					if (menu == MENU_BOARD)
					{
						hover_board(&mousePos);
					}
					else
					{
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
					}
					break;

				case SDL_KEYUP:
					switch (event.key.keysym.sym)
					{
						case SDLK_LEFT:
							scroll.x = 0;
							break;
						case SDLK_RIGHT:
							scroll.x = 0;
							break;
						case SDLK_UP:
							scroll.y = 0;
							break;
						case SDLK_DOWN:
							scroll.y = 0;
							break;
						case SDLK_PAGEUP:
							zoom = 0;
							break;
						case SDLK_PAGEDOWN:
							zoom = 0;
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
								focusedTextbox = gui->textboxUsername;
							}
							break;
						case SDLK_LEFT:
							scroll.x = 1;
							break;
						case SDLK_RIGHT:
							scroll.x = -1;
							break;
						case SDLK_UP:
							scroll.y = 1;
							break;
						case SDLK_DOWN:
							scroll.y = -1;
							break;
						case SDLK_PAGEUP:
							zoom = 1;
							break;
						case SDLK_PAGEDOWN:
							zoom = -1;
							break;
						case SDLK_F1:
							k -= 0.5;
							printf("%f\n", k);
							break;
						case SDLK_F2:
							k += 0.5;
							printf("%f\n", k);
							break;
						case SDLK_F12:
							debugMode = (debugMode + 1) % 4;
							break;
						// case SDLK_q:
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
									if (logged)
									{
										init_board(loggedAccount, textureMgr);
										menu = MENU_BOARD;
									}
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
									text_info_clear(gui->textInfo);
								}
								else if (SDL_PointInRect(&mousePos, gui->btnNext->bg->rect))
								{
									printf("\e[32m [INFO] : Le bouton Next a été cliqué ! ✨\e[37m\n");
									if (account_login(loggedAccount, gui->textboxUsername->text, gui->textboxPassword->text, gui->textInfo->text))
									{
										printf("Connexion échouée !\n");
									}
									else
									{
										logged = SDL_TRUE;
										printf("Connexion réussie ! %s\n", loggedAccount->nick);
										gui->textboxUsername->text[0] = 0;
										gui->textboxUsername->textLen = 0;
										textbox_update(gui->textboxUsername);
									}
									focusedTextbox = NULL;
									gui->textboxPassword->text[0] = 0;
									gui->textboxPassword->textLen = 0;
									textbox_update(gui->textboxPassword);
									text_info_update(gui->textInfo);
								}
								else if (SDL_PointInRect(&mousePos, gui->btnBack->bg->rect))
								{
									printf("\e[33m [INFO] : Le bouton Back a été cliqué ! ✨\e[37m\n");
									menu = MENU_MAIN;
									text_info_clear(gui->textInfo);
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
									if (account_create(gui->textboxUsername->text, gui->textboxPassword->text, gui->textInfo->text))
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
									text_info_update(gui->textInfo);
								}
								else if (SDL_PointInRect(&mousePos, gui->btnBack->bg->rect))
								{
									printf("\e[33m [INFO] : Le bouton Back a été cliqué ! ✨\e[37m\n");
									menu = MENU_LOGIN;
									text_info_clear(gui->textInfo);
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
							case MENU_BOARD:
								click_board(&mousePos);
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
		if ((board.camera.scale >= CAMERA_MIN_ZOOM && zoom == -1) || (board.camera.scale <= CAMERA_MAX_ZOOM && zoom == 1))
		{
			board.camera.scale += zoom * 0.02f * board.camera.scale;
			board.camera.origin.x += -19.8 * zoom /board.camera.scale;
			board.camera.origin.y += -10.80 * zoom /board.camera.scale;
		}
		board.camera.origin.x += scroll.x * (10/board.camera.scale);
		board.camera.origin.y += scroll.y * (10/board.camera.scale);
		//if (menu == MENU_BOARD)
			// update_board();

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

		clock_t end = clock();
		double time_spent = (time_spent  + (1000 * (double)(end - begin) / CLOCKS_PER_SEC))/2;
		frameCount++;

		switch (debugMode) {
			case 3:
				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
				for (int i = 0; i < WINDOW_WIDTH; i += WINDOW_WIDTH / 10)
				{
					SDL_RenderDrawLine(renderer, i, 0, i, WINDOW_HEIGHT);
				}
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
				for (int i = 0; i < WINDOW_HEIGHT; i += WINDOW_HEIGHT / 10)
				{
					SDL_RenderDrawLine(renderer, 0, i, WINDOW_WIDTH, i);
				}

			case 2:
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

				rect.w = 1;
				rect.h = WINDOW_HEIGHT;
				rect.x = WINDOW_WIDTH / 2 - rect.w / 2;
				rect.y = WINDOW_HEIGHT / 2 - rect.h / 2;
				SDL_RenderFillRect(renderer, &rect);

				rect.w = WINDOW_WIDTH;
				rect.h = 1;
				rect.x = WINDOW_WIDTH / 2 - rect.w / 2;
				rect.y = WINDOW_HEIGHT / 2 - rect.h / 2;
				SDL_RenderFillRect(renderer, &rect);

			case 1:
				if (frameCount%10 == 0)
				{
					sprintf(debugInfo->text, "time elapsed (ms) = %.2lf", time_spent);
					// printf("time elapsed (ms) = %.2lf\n", time_spent);
					frameCount = 0;
				}
				text_info_update(debugInfo);
				draw_sprite(debugInfo->sprite);
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

				rect.w = 20;
				rect.h = 4;
				rect.x = WINDOW_WIDTH / 2 - rect.w / 2;
				rect.y = WINDOW_HEIGHT / 2 - rect.h / 2;
				SDL_RenderFillRect(renderer, &rect);

				rect.w = 4;
				rect.h = 20;
				rect.x = WINDOW_WIDTH / 2 - rect.w / 2;
				rect.y = WINDOW_HEIGHT / 2 - rect.h / 2;
				SDL_RenderFillRect(renderer, &rect);

				SDL_SetRenderDrawColor(renderer, 50, 100, 50, 255);

				rect.w = 18;
				rect.h = 2;
				rect.x = WINDOW_WIDTH / 2 - rect.w / 2;
				rect.y = WINDOW_HEIGHT / 2 - rect.h / 2;
				SDL_RenderFillRect(renderer, &rect);

				rect.w = 2;
				rect.h = 18;
				rect.x = WINDOW_WIDTH / 2 - rect.w / 2;
				rect.y = WINDOW_HEIGHT / 2 - rect.h / 2;
				SDL_RenderFillRect(renderer, &rect);
				break;
			default:
			break;
		}

		SDL_RenderPresent(renderer);

		// FPS MGR
		frameLimit = SDL_GetTicks() + (1000/FPS_LIMIT);
		limit_fps(frameLimit);
	}

	exit_with_success();
	return EXIT_SUCCESS;
}
