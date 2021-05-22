#include <board.h>

Board board;
Resources resources;

void save_board(Board board, const char* path)
{
	FILE *file = fopen(path, "w");

	if (file == NULL)
	{
		char errorMsg[100];
		sprintf(errorMsg, "%s n'a pas pu être ouvert", path);
		exit_with_error(errorMsg);
	}

	fwrite(&board, sizeof(Board), 1, file);

	fclose(file);
}

Board load_board(const char* path)
{
	FILE *file = fopen(path, "r");
	Board board;

	if (file == NULL)
	{
		char errorMsg[100];
		sprintf(errorMsg, "%s n'a pas pu être ouvert", path);
		exit_with_error(errorMsg);
	}

	if(!feof(file))
		fread(&board, sizeof(Board), 1, file);
	fclose(file);
	return board;
}

// charge les tuiles dans l'ordre du plateau de jeu
void load_squares(Square *squares, int playerCount)
{
	int n = 2;
	if (playerCount < 5)
	{
		n = 1;
	}

	const int boardSquares[] = {
		SQUARE_INN, SQUARE_SHOP, SQUARE_TEMPLE, SQUARE_ENCOUNTER, SQUARE_PAN_RICE, SQUARE_HOTSPRING, SQUARE_PAN_MOUNT, SQUARE_FARM, SQUARE_SHOP, SQUARE_TEMPLE, SQUARE_ENCOUNTER, SQUARE_PAN_SEA, SQUARE_PAN_MOUNT, SQUARE_HOTSPRING,
		SQUARE_INN, SQUARE_PAN_SEA, SQUARE_TEMPLE, SQUARE_FARM, SQUARE_PAN_RICE, SQUARE_PAN_MOUNT, SQUARE_ENCOUNTER, SQUARE_TEMPLE, SQUARE_HOTSPRING, SQUARE_PAN_MOUNT, SQUARE_PAN_SEA, SQUARE_SHOP, SQUARE_FARM,
		SQUARE_INN, SQUARE_PAN_RICE, SQUARE_SHOP, SQUARE_ENCOUNTER, SQUARE_FARM, SQUARE_PAN_MOUNT, SQUARE_HOTSPRING, SQUARE_PAN_SEA, SQUARE_PAN_RICE, SQUARE_TEMPLE, SQUARE_FARM, SQUARE_ENCOUNTER, SQUARE_PAN_SEA, SQUARE_SHOP,
		SQUARE_INN, SQUARE_HOTSPRING, SQUARE_TEMPLE, SQUARE_ENCOUNTER, SQUARE_SHOP, SQUARE_PAN_SEA, SQUARE_FARM, SQUARE_HOTSPRING, SQUARE_ENCOUNTER, SQUARE_PAN_MOUNT, SQUARE_PAN_RICE, SQUARE_PAN_SEA, SQUARE_SHOP,
		SQUARE_INN
	};
	const int boardCapacities[] = {
		playerCount, n, 1, 1, 1, n, n, n, 1, n, 1, n, 1, 1,
		playerCount, 1, 1, n, n, n, n, 1, n, 1, n, 1, 1,
		playerCount, 1, 1, n, 1, n, 1, n, 1, n, n, 1, 1, n,
		playerCount, 1, n, 1, n, 1, n, n, 1, 1, n, n, 1,
		playerCount
	};

	squares[0].type.sprite.ai.offset.y = 0;
	for (int i = 0; i < BOARD_SQUARES; i++)
	{
		squares[i].type = *resources.squareTypes[boardSquares[i]];
		squares[i].type.sprite.ai.at = AT_CENTER;
		squares[i].type.sprite.ai.offset.x = 128 * i;
		squares[i].type.sprite.ai.offset.y = squares[i - 1].type.sprite.ai.offset.y + (rand() % 150 - 75);
		squares[i].type.sprite.ai.size.w = 128;
		squares[i].type.sprite.ai.size.h = 128;
		squares[i].capacity = boardCapacities[i];
	}
}

void init_board(Account* loggedAccount, TextureMgr* textureMgr)
{
	char nameTagText[110];
	srand(time(NULL));

	board.squareId = SQUARE_INN;
	board.mode     = BM_BOARD;
	reset_recap(&board.recap);

	board.sgui = NULL;
	board.lastInnPos = -1;

	// Initialisation des joueurs
	int travId[TRAVELERS];
	for (int i = 0; i < TRAVELERS; i++)
	{
		travId[i] = i;
	}
	shuffle(travId, TRAVELERS);

	int roadDist[BOARD_PLAYERS];
	for (int i = 0; i < BOARD_PLAYERS; i++)
	{
		roadDist[i] = i;
	}
	shuffle(roadDist, BOARD_PLAYERS);

	printf(" \e[34m◁ Liste des Joueurs ▷\e[37m\n");
	for (int i = 0; i < BOARD_PLAYERS; i++)
	{
		board.players[i].traveler = *resources.travelers[travId[i]];
		if (i == 0) // debug 0
		{
			// pour tester un voyageur spécifique
			// board.players[i].traveler = *resources.travelers[8];
			sprintf(board.players[i].nickname, "%s", loggedAccount->nick);
			board.players[i].isHuman = SDL_TRUE;
		}
		else
		{
			// sprintf(board.players[i].nickname, "Joueur %d", i + 1);
			strcpy(board.players[i].nickname, board.players[i].traveler.name);
			board.players[i].isHuman = SDL_FALSE;
		}
		sprintf(nameTagText, "  %s  ", board.players[i].nickname);
		board.players[i].nameTag = new_text(nameTagText, 255, 255, 255, 0.5);
		board.players[i].position = 0;
		board.players[i].roadDist = roadDist[i];
		board.players[i].bundleToken = 0;
		board.players[i].coins = board.players[i].traveler.startCoins;
		board.players[i].templeCoins = 0;
		board.players[i].hotSpringCount = 0;
		board.players[i].foodCount = 0;
		board.players[i].itemCount = 0;
		board.players[i].encounterCount = 0;
		board.players[i].panRice = 0;
		board.players[i].panMount = 0;
		board.players[i].panSea = 0;
		board.players[i].state = STATE_IDLE;
		// printf("[%d] %d %d %d %d\n", i, board.players[i].traveler.sprite.ai.offset.x, board.players[i].traveler.sprite.ai.offset.y, board.players[i].traveler.sprite.ai.size.w, board.players[i].traveler.sprite.ai.size.h);

		printf(" \e[34m · %s\t: %s\e[37m\n", board.players[i].nickname, board.players[i].traveler.name);
		board.playerCount++;
	}

	load_squares(board.squares, board.playerCount);
	board.squareCount = BOARD_SQUARES;

	for (int i = 0; i < BOARD_SQUARES; i++)
	{
		board.squares[i].state = STATE_IDLE;
		board.squares[i].position = i;
	}

	for (int i = 0; i < BOARD_PLAYERS; i++)
	{
		board.players[i].traveler.sprite.ai.at = AT_CENTER;
		board.players[i].traveler.sprite.ai.size.w = 100;
		board.players[i].traveler.sprite.ai.size.h = 100;
		update_player_ai(&board.players[i]);
	}

	board.lboard = new_lboard(board.players, board.playerCount);
	update_lboard(board.lboard, board.players, board.playerCount);

	board.camera.origin.x = -500;
	board.camera.origin.y = 300;
	board.camera.scale    = 1.f;

	board.drawLboard = SDL_FALSE;
	board.started = SDL_FALSE;
}

SDL_bool is_game_started()
{
	return board.started;
}

void board_update()
{
	int scrollX = 0;
	int scrollY = 0;
	int zoom = 0;

	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_TAB])
		board.drawLboard = SDL_TRUE;
	else
		board.drawLboard = SDL_FALSE;

	if (board.mode == BM_BOARD)
	{
		if (state[SDL_SCANCODE_LEFT])
			scrollX += 1;
		if (state[SDL_SCANCODE_RIGHT])
			scrollX -= 1;
		if (state[SDL_SCANCODE_UP])
			scrollY += 1;
		if (state[SDL_SCANCODE_DOWN])
			scrollY -= 1;
		if (state[SDL_SCANCODE_PAGEUP])
			zoom += 1;
		if (state[SDL_SCANCODE_PAGEDOWN])
			zoom -= 1;
		if ((board.camera.scale >= CAMERA_MIN_ZOOM && zoom == -1) || (board.camera.scale <= CAMERA_MAX_ZOOM && zoom == 1))
		{
			board.camera.scale += zoom * 0.02f * board.camera.scale;
			// board.camera.origin.x += -19.8 * zoom /board.camera.scale;
			// board.camera.origin.y += -10.80 * zoom /board.camera.scale;
		}
		board.camera.origin.x += scrollX * (10/board.camera.scale);
		board.camera.origin.y += scrollY * (10/board.camera.scale);
	}

	if (SDL_GetTicks() > board.waitUntil && board.waitUntil)
	{
		board.waitUntil = 0;
		begin_turn();
	}
}

void board_event(SDL_Event* event, SDL_Point* mousePos)
{
	switch (event->type)
	{
		case SDL_MOUSEMOTION:
			board_mouse(mousePos, SDL_FALSE);
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (board.playing != NULL && !board.waitUntil)
			{
				if (board.playing->isHuman)
					board_mouse(mousePos, SDL_TRUE);
			}
			break;
		case SDL_KEYDOWN:
			switch (event->key.keysym.sym)
			{
				case SDLK_RETURN:
					if (board.mode == BM_BOARD)
					{
						if (board.playing != NULL)
							update_hud(board.hud, *board.playing);
						random_move();
					}
			}
			break;
	}
}

void board_mouse(SDL_Point* mousePos, SDL_bool click)
{
	SDL_Rect rect;

	if (board.mode == BM_BOARD)
	{
		for (int i = 0; i < board.playerCount; i++)
		{
			if (board.players[i].state == STATE_DISABLED)
				continue;
			AnchorInfo ai = board.players[i].traveler.sprite.ai;
			camera_ai(&ai, board.camera);
			rect = anchored_rect(ai, NULL);
			if (SDL_PointInRect(mousePos, &rect))
			{
				if (click)
					board.players[i].state = STATE_CLICKED;
				else
					board.players[i].state = STATE_HOVERED;
			}
			else
			{
				board.players[i].state = STATE_IDLE;
			}
		}
		for (int position = 0; position < BOARD_SQUARES; position++)
		{
			if (board.squares[position].state == STATE_DISABLED)
				continue;
			AnchorInfo ai = board.squares[position].type.sprite.ai;
			camera_ai(&ai, board.camera);
			rect = anchored_rect(ai, NULL);
			if (SDL_PointInRect(mousePos, &rect))
			{
				if (click)
				{
					board.squares[position].state = STATE_CLICKED;
					move_player(&board.squares[position]);
					square_action(&board.squares[position]);
				}
				else
				{
					board.squares[position].state = STATE_HOVERED;
				}
			}
			else
			{
				board.squares[position].state = STATE_IDLE;
			}
		}
	}
	else
	{
		for (int i = 0; i < board.sgui->frameCount; i++)
		{
			if (board.sgui->frames[i]->state == STATE_DISABLED)
				continue;
			SDL_Rect rect = anchored_rect(board.sgui->frames[i]->ai, NULL);
			if (SDL_PointInRect(mousePos, &rect))
			{
				if (click)
				{
					board.sgui->frames[i]->state = STATE_CLICKED;
					// printf("\e[31m [DEBUG] BUY : %s\e[37m\n", board.sgui->frames[i]->content.food.name);
					if (buy_from_frame(board.playing, board.sgui->frames[i]))
					{
						if (board.sgui->frames[i]->contentType == CONTENT_FOOD)
						{
							board.innFoods[i] = NULL;
							// board.recap.foods[board.recap.foodCount] = board.sgui->frames[i]->content.food;
							// board.recap.foodCount++;
							for (int j = 0; j < board.sgui->frameCount; j++)
							{
								board.sgui->frames[j]->state = STATE_DISABLED;
							}
						}
						else if (board.sgui->frames[i]->contentType == CONTENT_ITEM)
						{
							// board.recap.items[board.recap.itemCount] = board.sgui->frames[i]->content.item;
							// board.recap.itemCount++;
							if (board.playing->traveler.id == TRAVELER_ZEN_EMON) 	// Prix 1 pièce
							{
								// reset prix au second achat
								for(int i = 0; i < board.sgui->frameCount; i++)
								{
									board.sgui->frames[i]->content.item.price = resources.items[board.sgui->frames[i]->content.item.id]->price;
									sprintf(board.sgui->frames[i]->coinText->content, "%d", board.sgui->frames[i]->content.food.price);
									update_text(board.sgui->frames[i]->coinText);
								}
							}
							for (int j = 0; j < board.sgui->frameCount; j++)
							{
								sprintf(board.sgui->frames[j]->bundleTkText->content, "%d", tk_from_collection(board.sgui->frames[j]->content.item, board.playing->items, board.playing->itemCount));
								update_text(board.sgui->frames[j]->bundleTkText);
								// printf("TK UPDATE %s\n", board.sgui->frames[j]->bundleTkText->content);
							}
						}
					}
					update_hud(board.hud, *board.playing);
				}
				else
				{
					board.sgui->frames[i]->state = STATE_HOVERED;
				}
			}
			else
			{
				board.sgui->frames[i]->state = STATE_IDLE;
			}
		}

		for (int btnId = 0; btnId < board.sgui->menu->buttonCount; btnId++)
		{
			if (board.sgui->menu->buttons[btnId]->state == STATE_DISABLED)
				continue;
			SDL_Rect rect = anchored_rect(board.sgui->menu->buttons[btnId]->bg.ai, board.sgui->menu->buttons[btnId]->bg.parent);
			if (SDL_PointInRect(mousePos, &rect))
			{
				if (click)
				{
					board.sgui->menu->buttons[btnId]->state = STATE_CLICKED;
					// button_action(board.sgui->menu->buttons[btnId], &mid);
					if (board.sgui->menu->buttons[btnId]->action == ACTION_END_TURN)
					{
						board.mode = BM_BOARD;
						end_turn();
					}
					else if (board.sgui->menu->buttons[btnId]->action == ACTION_TEMPLE)
					{
						action_temple(board.playing, &board.recap);
						update_hud(board.hud, *board.playing);
						if (board.recap.templeCoins == 3 || board.playing->coins == 0)
						{
							board.sgui->menu->buttons[btnId]->state = STATE_DISABLED;
						}
					}
				}
				else
				{
					board.sgui->menu->buttons[btnId]->state = STATE_HOVERED;
				}
			}
			else
			{
				board.sgui->menu->buttons[btnId]->state = STATE_IDLE;
			}
		}
	}
}

void update_player_ai(Player* player)
{
	player->traveler.sprite.ai.offset.x = player->position * 128;
	player->traveler.sprite.ai.offset.y = board.squares[player->position].type.sprite.ai.offset.y - 128 * (player->roadDist + 1);
}

void camera_ai(AnchorInfo* ai, Camera camera)
{
	ai->offset.x = (ai->offset.x + camera.origin.x) * camera.scale;
	ai->offset.y = (ai->offset.y + camera.origin.y) * camera.scale;
	ai->size.w = ai->size.w * camera.scale;
	ai->size.h = ai->size.h * camera.scale;
}

void camera_draw_sprite(Sprite* sprite, Camera camera)
{
	AnchorInfo ai = sprite->ai;
	camera_ai(&ai, camera);
	SDL_Rect rect = anchored_rect(ai, sprite->parent);

	SDL_RenderCopy(renderer, sprite->tex, sprite->crop, &rect);
	if (debugMode)
	{
		SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
		SDL_RenderDrawRect(renderer, &rect);
	}
}

// todo
void draw_char_sel_gui()
{
	for (int i = 0; i < TRAVELERS; i++)
	{
		draw_sprite(&resources.travelers[i]->sprite);
	}
}

void draw_lines(int squareCount)
{
	if (!squareCount)
		return;

	for (int position = 0; position < squareCount; position++)
	{
		for (int j = 0; j < board.squares[position].capacity; j++)
		{
			SDL_SetRenderDrawColor(renderer, board.squares[position].type.color.r, board.squares[position].type.color.g, board.squares[position].type.color.b, 255);
			AnchorInfo ai = board.squares[position].type.sprite.ai;
			ai.offset.y = ai.offset.y - 128/2 - 128 * j;
			ai.size.w = 4;
			camera_ai(&ai, board.camera);

			SDL_Rect rect = anchored_rect(ai, NULL);

			if (is_rect_on_screen(&rect))
			{
				SDL_RenderFillRect(renderer, &rect);
			}
			ai = board.squares[position].type.sprite.ai;
			ai.offset.y = ai.offset.y - 128 * (j + 1);
			ai.size.w = 20;
			ai.size.h = 20;
			camera_ai(&ai, board.camera);
			rect = anchored_rect(ai, NULL);

			if (is_rect_on_screen(&rect))
			{
				SDL_SetTextureColorMod(board.squares[position].type.sprite.tex, board.squares[position].type.color.r, board.squares[position].type.color.g, board.squares[position].type.color.b);
				SDL_RenderCopy(renderer, resources.squareTypes[9]->sprite.tex, resources.squareTypes[9]->sprite.crop, &rect);
				SDL_SetTextureColorMod(board.squares[position].type.sprite.tex, 255, 255, 255);
			}
		}
	}
}

void draw_squares()
{
	for (int position = 0; position < board.squareCount; position++)
	{
		state_color_mod(board.squares[position].type.sprite.tex, &board.squares[position].state);
		camera_draw_sprite(&board.squares[position].type.sprite, board.camera);
		SDL_SetTextureColorMod(board.squares[position].type.sprite.tex, 255, 255, 255);
	}
}

void draw_players()
{
	// SDL_Rect rect;
	for (int i = 0; i < board.playerCount; i++)
	{
		state_color_mod(board.players[i].traveler.sprite.tex, &board.players[i].state);
		camera_draw_sprite(&board.players[i].traveler.sprite, board.camera);
		SDL_SetTextureColorMod(board.players[i].traveler.sprite.tex, 255, 255, 255);
	}
	for (int i = 0; i < board.playerCount; i++)
	{
		if (board.players[i].state == STATE_HOVERED || board.players[i].state == STATE_CLICKED)
		{
			board.players[i].nameTag->sprite->ai.at = AT_CENTER;
			board.players[i].nameTag->sprite->ai.offset.x = board.players[i].traveler.sprite.ai.offset.x - board.players[i].nameTag->sprite->ai.size.w - 10;
			board.players[i].nameTag->sprite->ai.offset.y = board.players[i].traveler.sprite.ai.offset.y;
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
			AnchorInfo ai = board.players[i].nameTag->sprite->ai;
			camera_ai(&ai, board.camera);
			SDL_Rect rect = anchored_rect(ai, NULL);
			SDL_RenderFillRect(renderer, &rect);
			camera_draw_sprite(board.players[i].nameTag->sprite, board.camera);
		}
	}
}

void draw_board()
{
	// draw_char_sel_gui();
	switch (board.mode)
	{
		case BM_SQUARE:
			draw_square_gui(board.sgui);
			break;
		case BM_BOARD:
			// draw_bg(); // Affiche l'arrière plan du plateau
			draw_sprite(&textureMgr->bg[6]);
			draw_lines(board.squareCount);
			draw_squares(&board);
			draw_players();
			break;
		case BM_INVENTORY:
			break;
	}

	if (board.drawLboard)
	{
		draw_lboard(board.lboard);
	}

	draw_hud(board.hud);
}

int whos_turn_is_it()
{
	int minPos = BOARD_SQUARES;
	int maxRoadDist = -1;
	int playerId;
	for (int i = 0; i < board.playerCount; i++)
	{
		if (board.players[i].position < minPos)
			minPos = board.players[i].position;
	}
	for (int i = 0; i < board.playerCount; i++)
	{
		if (board.players[i].position == minPos)
		{
			if (board.players[i].roadDist > maxRoadDist)
			{
				maxRoadDist = board.players[i].roadDist;
				playerId = i;
			}
		}
	}
	// printf("Next move : %s\n", resources.travelers[board.players[playerId].traveler].name);
	return playerId;
}

int highlight_possible_moves(Player player)
{
	int possibilities = 0;
	for (int position = 0; position < BOARD_SQUARES; position++)
	{
		if (is_move_allowed(position, player))
		{
			possibilities++;
			board.squares[position].state = STATE_IDLE;
		}
		else
		{
			board.squares[position].state = STATE_DISABLED;
		}
	}

	return possibilities;
}

SDL_bool is_move_allowed(int position, Player player)
{
	int next_inn;
	int space = board.squares[position].capacity;

	for (int i = player.position + 1; i < BOARD_SQUARES; i++)
	{

		if (board.squares[i].type.id == SQUARE_INN)
		{
			next_inn = i;
			break;
		}
	}
	// printf("next inn : %d\n", next_inn);
	if (position > next_inn)
		return SDL_FALSE;

	if (position <= player.position)
		return SDL_FALSE;

	for (int i = 0; i < board.playerCount; i++)
	{
		if (board.players[i].position == position)
			space--;
	}
	if (space <= 0)
		return SDL_FALSE;

	if ((board.squares[position].type.id == SQUARE_SHOP || board.squares[position].type.id == SQUARE_TEMPLE) && player.coins == 0)
		return SDL_FALSE;

	if (board.squares[position].type.id == SQUARE_PAN_RICE && player.panRice == 3)
		return SDL_FALSE;
	if (board.squares[position].type.id == SQUARE_PAN_MOUNT && player.panMount == 4)
		return SDL_FALSE;
	if (board.squares[position].type.id == SQUARE_PAN_SEA && player.panSea == 5)
		return SDL_FALSE;

	return SDL_TRUE;
}

void random_move()
{
	int playerId = whos_turn_is_it();
	int possibleSquares[4];
	int possibilities = 0;
	for (int position = board.players[playerId].position + 1; position < BOARD_SQUARES; position++)
	{
		if (is_move_allowed(position, board.players[playerId]))
		{
			possibleSquares[possibilities] = position;
			possibilities++;
		}
		if (possibilities == 4)
			break;
	}
	if (possibilities == 0)
	{
		printf("\e[34m [DEBUG] Game over !\e[37m\n");
		for (int i = 0; i < board.playerCount; i++)
		{
			printf("\e[34m   - %s :\n", board.players[i].nickname);
			printf("     Pièces = %d\n", board.players[i].coins);
			printf("     Points de Victoire = %d\n", board.players[i].bundleToken);
			printf("     Pièce au temple = %d\e[37m\n\n", board.players[i].templeCoins);
		}
		return;
	}
	shuffle(possibleSquares, possibilities);
	int position = -1;
	if (board.playing->coins < 2)
	{
		for (int i = 0; i < possibilities; i++)
		{
			if (board.squares[possibleSquares[i]].type.id == SQUARE_FARM)
				position = possibleSquares[i];
			else if (board.squares[possibleSquares[i]].type.id == SQUARE_ENCOUNTER  && position < 0)
				position = possibleSquares[i];
		}
	}
	else if (board.playing->coins > 5)
	{
		for (int i = 0; i < possibilities; i++)
		{
			if (board.squares[possibleSquares[i]].type.id == SQUARE_SHOP)
				position = possibleSquares[i];
		}
	}
	if (position < 0)
	{
		position = possibleSquares[0];
	}

	int space = board.squares[position].capacity;
	for (int i = 0; i < board.playerCount; i++)
	{
		if (board.players[i].position == position)
			space--;
	}
	board.players[playerId].position = position;
	board.players[playerId].roadDist = board.squares[position].capacity - space;
	update_player_ai(&board.players[playerId]);
	square_action(&board.squares[position]);
	end_turn();
}

void move_player(Square* square)
{
	int space = square->capacity;
	for (int i = 0; i < board.playerCount; i++)
	{
		if (board.players[i].position == square->position)
			space--;
	}
	board.playing->position = square->position;
	board.playing->roadDist = square->capacity - space;
	update_player_ai(board.playing);
}

void begin_turn()
{
	reset_recap(&board.recap);
	board.playing = &board.players[whos_turn_is_it()];
	// for (int i = 0; i < board.playerCount; i++)
	// {
	// 	log_player(board.players[i].bundleToken, i == board.playerCount - 1);
	// }
	board.hud = new_hud(*board.playing);
	highlight_possible_moves(*board.playing);
	if (!board.started)
	{
		board.started = SDL_TRUE;
		board.waitUntil = SDL_GetTicks() + 2000;
		return;
	}
	if (!board.playing->isHuman)
	{
		random_move();
	}
	printf(" BEGIN TURN\n");
}

void end_turn()
{
	printf(" END TURN\n");
	board.mode = BM_BOARD;
	update_lboard(board.lboard, board.players, board.playerCount);

	// board.playing = &board.players[whos_turn_is_it()];
	highlight_possible_moves(*board.playing);
	destroy_hud(board.hud);
	board.hud = new_hud(*board.playing);
	board.waitUntil = SDL_GetTicks() + 500; // + 200; // + 5000;
	printf("\e[32m [RECAP] %d %d %d\e[37m\n", board.recap.coins, board.recap.bundleToken, board.recap.templeCoins);
}

// Bonus à faire :
// - Hiroshige l'artiste : panorama choisi au relai
// - Chuubei le messager : rencontre au relai
// - Yoshiyasu le fonctionnaire : 2 rencontres au choix
// - Satsuki l'orpheline : plat gratuit au relai (refus possible)
// - Sasayakko la geisha : objet le moins cher offert
void square_action(Square* square)
{
	Item* items[3];
	int tk, encounterId, minPrice = 999, minPriceId;
	char obtained[256];
	printf("SQUARE ACTION = %s %d\n", board.playing->nickname, square->type.id);

	board.squareId = square->type.id;
	board.mode = BM_SQUARE;
	switch (square->type.id)
	{
		case SQUARE_INN:
			// printf("\e[35mLAST INN %d %d\e[37m\n", board.playing->position, board.lastInnPos);
			if (board.lastInnPos != board.playing->position)
			{
				init_inn(board.innFoods);
				printf("\e[35m [Inn] Food initialized!\e[37m\n");
				board.lastInnPos = board.playing->position;
			}

			if (board.playing->traveler.id == TRAVELER_HIROSHIGE) 	// Menu Custom pour choix du panorama
			{

			}
			else if (board.playing->traveler.id == TRAVELER_SATSUKI) 	// Menu Custom pour accepter ou non le repas gratuit
			{

			}

			board.sgui = new_inn_gui(board.innFoods, board.playerCount + 1);

			if (board.playing->traveler.id == TRAVELER_KINKO) 	// Prix réduit
			{
				for (int i = 0; i < board.sgui->frameCount; i++)
				{
					board.sgui->frames[i]->content.food.price--;
					sprintf(board.sgui->frames[i]->coinText->content, "%d", board.sgui->frames[i]->content.food.price);
					update_text(board.sgui->frames[i]->coinText);
				}
			}

			if (!board.playing->isHuman)
			{
				for (int i = 0; i < board.sgui->frameCount; i++)
				{
					if (board.sgui->frames[i]->content.food.price < minPrice)
					{
						minPrice = board.sgui->frames[i]->content.food.price;
						minPriceId = i;
					}
				}
				if (buy_from_frame(board.playing, board.sgui->frames[minPriceId]))
				{
					board.innFoods[minPriceId] = NULL;
				}

				// for (int i = 0; i < board.sgui->frameCount; i++)
				// {
				// 	// printf("%d\n", i);
				// 	if (board.sgui->frames[i]->sold == SDL_TRUE || board.innFoods[i] == NULL)
				// 	{
				// 		continue;
				// 		// printf(".");
				// 	}
				// 	else if (buy_from_frame(board.playing, board.sgui->frames[i]))
				// 	{
				// 		board.innFoods[i] = NULL;
				// 		break;
				// 	}
				// }
			}
			break;
		case SQUARE_SHOP:
			init_shop(items);
			board.sgui = new_shop_gui(items, board.playing);
			if (board.playing->traveler.id == TRAVELER_ZEN_EMON) 	// Prix 1 pièce
			{
				for (int i = 0; i < board.sgui->frameCount; i++)
				{
					board.sgui->frames[i]->content.item.price = 1;
					sprintf(board.sgui->frames[i]->coinText->content, "%d", board.sgui->frames[i]->content.food.price);
					update_text(board.sgui->frames[i]->coinText);
				}
			}
			if (!board.playing->isHuman)
			{
				for (int i = 0; i < 3; i++)
				{
					minPriceId = -1;
					for (int j = 0; j < 3; j++)
					{
						if (board.sgui->frames[j]->sold)
							continue;
						if (board.sgui->frames[j]->content.item.price < minPrice)
						{
							minPrice = board.sgui->frames[j]->content.item.price;
							minPriceId = j;
						}
					}
					if (minPriceId == -1)
						break;
					printf("here\n");
					if (buy_from_frame(board.playing, board.sgui->frames[minPriceId]))
					{
						if (board.playing->coins < 5 && (rand() % 3 == 0 || board.playing->coins < 3))
							break;
					}
				}
			}
			break;
		case SQUARE_HOTSPRING:
			tk = init_hot_spring();
			if (board.playing->traveler.id == TRAVELER_MITSUKUNI)
				tk++;
			board.sgui = new_hot_spring_gui(tk);
			action_hot_spring(board.playing, tk);
			break;
		case SQUARE_TEMPLE:
			if (board.playing->traveler.id == TRAVELER_HIROTADA) 	// Piece gratuite au temple
			{
				board.playing->templeCoins += 1 ;
			}
			board.sgui = new_temple_gui();
			if (!board.playing->isHuman)
			{
				for (int i = 0; i < 3; i++) {
					if (action_temple(board.playing, &board.recap))
					{
						if (board.playing->coins < 5 && (rand() % 3 == 0 || board.playing->coins < 3))
							break;
					}
					else
					{
						break;
					}
				}
			}
			break;
		case SQUARE_ENCOUNTER:
			if (board.playing->traveler.id == TRAVELER_UMEGAE)		// +1 Coins et +1 Point de victoire pour les recontres
			{
				board.playing->coins += 1;
				board.playing->bundleToken += 1;
			}
			encounterId = init_encounter(board.playing);
			action_encounter(board.playing, encounterId, obtained);
			board.sgui = new_encounter_gui(encounterId, obtained);
			break;
		case SQUARE_FARM:
			board.sgui = new_farm_gui();
			action_farm(board.playing);
			break;
		case SQUARE_PAN_RICE:
			action_pan_rice(board.playing);
			board.sgui = new_pan_rice_gui(board.playing->panRice);
			break;
		case SQUARE_PAN_MOUNT:
			action_pan_mount(board.playing);
			board.sgui = new_pan_mount_gui(board.playing->panMount);
			break;
		case SQUARE_PAN_SEA:
			action_pan_sea(board.playing);
			board.sgui = new_pan_sea_gui(board.playing->panSea);
			break;
	}
	update_hud(board.hud, *board.playing);
}
