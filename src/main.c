// Tokaido by QUINTO Esteban & SERANDER Paul (C) 2021
#include <utility.h>
#include <gui.h>
#include <time.h>
#include <stdlib.h>
#include <game.h>
#include <board.h>
#include <account.h>

// Menu accessible avec <F12>
void debug_aff(int debugMode, Text* debugText, double time_spent);

int frameCount = 0;

int main(int argc, const char *argv[])
{
	double startedAt = SDL_GetTicks(); // pour le délai du splash screen
	init(); // initialisation du renderer/window
	init_fps_counter(); // pour le nombre de FPS dans le menu debug
	show_splash_screen(); // affiche le splash screen le temps du chargement
	// SDL_SetCursor(init_system_cursor(arrow));
	Account* loggedAccount = guest_account();
	SDL_bool logged = SDL_FALSE; // SDL_FALSE debug

	// chargement de toutes les images utilisées dans le jeu
	load_textures();
	load_resources();


	Gui* gui = init_gui();
	MenuId menuId = MENU_MAIN;
	Menu* menu = gui->menus[menuId];

	init_char_sel(gui->charSelMenu->sprites[1], gui->charSelMenu->sprites[2], gui->charSelMenu->buttons[0]->text->content, gui->charSelMenu->buttons[1]->text->content);
	update_text(gui->charSelMenu->buttons[0]->text);
	update_text(gui->charSelMenu->buttons[1]->text);

	SDL_Point mousePos;

	Textbox* focusedTextbox = NULL;
	Button* clickedButton = NULL;

	// debug
	Text* debugText = new_text("Loading debug info...", 255, 255, 255, 0.45);
	debugText->sprite->ai.at = AT_BOTTOM_LEFT;
	debugText->sprite->ai.offset.x = 10;
	debugText->sprite->ai.offset.y = 10;

	while (SDL_GetTicks() - startedAt < 500) // pour que le splash screen reste au moins 500ms
	{
		SDL_Delay(100);
	}

	while (program_launched) // boucle principale
	{
		update_fps_counter();
		clock_t begin = clock(); // pour connaitre le temps de calcul de chaque frame

		SDL_Event event;
		SDL_GetMouseState(&mousePos.x, &mousePos.y);

		// change la couleur des boutons au survol
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

		// récupération de tous les event
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
						case SDLK_F12:
							debugMode = (debugMode + 1) % 4;
							break;
						case SDLK_ESCAPE: // retourne au menu principal
							if (menuId == MENU_MAIN)
								program_launched = SDL_FALSE;
							// else
							// {
							// 	menu = gui->mainMenu;
							// 	menuId = MENU_MAIN;
							// }
							break;
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					// clic des boutons
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
					// s'adapte à la fenêtre quand elle est redimensionée
					SDL_GetWindowSize(window, &windowAnchor.size.w, &windowAnchor.size.h);
					break;
				case SDL_QUIT:
					program_launched = SDL_FALSE;
					break;
			}
			if (menuId == MENU_BOARD)
			{
				// s'occupe des event du plateau
				board_event(&event, &mousePos, &menuId);
			}
		}

		// actions des boutons après le petit délai
		if (SDL_GetTicks() > clickedUntil && clickedUntil && clickedButton != NULL)
		{
			if (clickedButton->action == ACTION_LOGIN)
			{
				if (account_login(loggedAccount, gui->loginMenu->textboxes[0]->text->content, gui->loginMenu->textboxes[1]->text->content, gui->loginMenu->texts[3]->content))
				{
					printf("Connexion échouée ! [%s]\n", gui->loginMenu->textboxes[1]->text->content);
				}
				else
				{
					logged = SDL_TRUE;
					printf("Connexion réussie ! %s\n", loggedAccount->nick);
				}
				sprintf(gui->archivesMenu->texts[2]->content, "Nombre de victoires : %d", loggedAccount->wonGames);
				sprintf(gui->archivesMenu->texts[3]->content, "Nombre de défaites  : %d", loggedAccount->lostGames);
				sprintf(gui->archivesMenu->texts[4]->content, "Connecté en tant que : %s", loggedAccount->nick);
				update_text(gui->archivesMenu->texts[2]);
				update_text(gui->archivesMenu->texts[3]);
				update_text(gui->archivesMenu->texts[4]);
				gui->loginMenu->textboxes[1]->text->content[0] = 0;
				gui->loginMenu->textboxes[1]->textLen = 0;
				update_text(gui->loginMenu->textboxes[1]->text);
				update_text(gui->loginMenu->texts[3]);

			}
			else if (clickedButton->action == ACTION_SIGNUP)
			{
				if (account_create(gui->signupMenu->textboxes[0]->text->content, gui->signupMenu->textboxes[1]->text->content, gui->signupMenu->texts[3]->content))
				{
					printf("Création de compte échouée !\n");
				}
				else
				{
					printf("Création de compte réussie !\n");
				}
				gui->signupMenu->textboxes[1]->text->content[0] = 0;
				gui->signupMenu->textboxes[1]->textLen = 0;
				update_text(gui->signupMenu->textboxes[1]->text);
				update_text(gui->signupMenu->texts[3]);
			}
			else if (clickedButton->action == ACTION_DEL_ACC)
			{
				if (logged)
					account_delete(loggedAccount->id, menu->texts[1]->content);
				else
					sprintf(menu->texts[1]->content, "Vous n'êtes pas connecté !");
				update_text(menu->texts[1]);
				logged = SDL_FALSE;
				loggedAccount = guest_account();
			}
			else if (clickedButton->action == ACTION_LOGOUT)
			{
				if (logged)
				{
					strcpy(menu->texts[1]->content, "Déconnexion réussie !");
					logged = SDL_FALSE;
					loggedAccount = guest_account();
					strcpy(gui->archivesMenu->texts[2]->content, "Nombre de victoires : _");
					strcpy(gui->archivesMenu->texts[3]->content, "Nombre de défaites  : _");
					strcpy(gui->archivesMenu->texts[4]->content, "Connecté en tant que : Invité");
					update_text(gui->archivesMenu->texts[2]);
					update_text(gui->archivesMenu->texts[3]);
					update_text(gui->archivesMenu->texts[4]);
				}
				else
				{
					strcpy(menu->texts[1]->content, "Vous n'êtes pas connecté !");
				}
				update_text(menu->texts[1]);
			}
			else
			{
				if (clickedButton->action == ACTION_START_SOLO_1)
					init_board(loggedAccount, textureMgr, 0);
				else if (clickedButton->action == ACTION_START_SOLO_2)
					init_board(loggedAccount, textureMgr, 1);

				button_action(clickedButton, &menuId);
				if (clickedButton->nextMenuId == MENU_ARCHIVES)
				{
					strcpy(gui->archivesMenu->texts[1]->content, "");
					if (logged)
					{
						sprintf(gui->archivesMenu->texts[2]->content, "Nombre de victoires : %d", loggedAccount->wonGames);
						sprintf(gui->archivesMenu->texts[3]->content, "Nombre de défaites  : %d", loggedAccount->lostGames);
					}
					update_text(gui->archivesMenu->texts[1]);
					update_text(gui->archivesMenu->texts[2]);
					update_text(gui->archivesMenu->texts[3]);
				}
				else if (clickedButton->nextMenuId == MENU_SIGNUP || clickedButton->nextMenuId == MENU_LOGIN)
				{
					strcpy(gui->loginMenu->texts[3]->content, "");
					update_text(gui->loginMenu->texts[3]);
					strcpy(gui->signupMenu->texts[3]->content, "");
					update_text(gui->signupMenu->texts[3]);
				}
			}
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
			// déroulement de la partie
			if (!is_game_started())
			{
				begin_turn();
			}
			board_update();
			draw_board();
		}
		else
		{
			// affiche les menus conventionnels
			draw_menu(menu);
			menu = gui->menus[menuId];
		}

		clock_t end = clock();
		double time_spent = (1000 * (double)(end - begin) / CLOCKS_PER_SEC);
		frameCount++;
		// calcul du temps de rendu pour l'affichage de debug

		debug_aff(debugMode, debugText, time_spent);

		SDL_RenderPresent(renderer);
	}

	exit_with_success();
	return EXIT_SUCCESS;
}

// affichage du menu de debugging
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
