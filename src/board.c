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
	srand(time(NULL));

	board.camera.origin.x = 0;
	board.camera.origin.y = 0;
	board.camera.scale    = 1.f;

	board.squareId = SQUARE_INN;
	board.mode     = BM_BOARD;

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

	printf(" \e[32m◁ Liste des Joueurs ▷\e[37m\n");
	for (int i = 0; i < BOARD_PLAYERS; i++)
	{
		board.players[i].traveler = *resources.travelers[travId[i]];
		if (i == 0)
		{
			sprintf(board.players[i].nickname, "%s", loggedAccount->nick);
			board.players[i].isHuman = SDL_FALSE;
		}
		else
		{
			sprintf(board.players[i].nickname, "Joueur %d", i + 1);
			board.players[i].isHuman = SDL_FALSE;
		}
		board.players[i].nameTag = new_text(board.players[i].nickname, 255, 255, 255, 0.5);
		board.players[i].position = 0;
		board.players[i].roadDist = roadDist[i];
		board.players[i].bundleToken = 0;
		board.players[i].coins = board.players[i].traveler.startCoins;
		board.players[i].templeCoins = 0;
		board.players[i].hotSpring = 0;
		board.players[i].foodCount = 0;
		board.players[i].itemCount = 0;
		board.players[i].encounterCount = 0;
		board.players[i].panRice = 0;
		board.players[i].panMount = 0;
		board.players[i].panSea = 0;
		board.players[i].state = STATE_IDLE;
		// printf("[%d] %d %d %d %d\n", i, board.players[i].traveler.sprite.ai.offset.x, board.players[i].traveler.sprite.ai.offset.y, board.players[i].traveler.sprite.ai.size.w, board.players[i].traveler.sprite.ai.size.h);

		printf(" \e[32m · %s\t: %s\e[37m\n", board.players[i].nickname, board.players[i].traveler.name);
		board.playerCount++;
	}

	// board.squareGui = init_square_gui(textureMgr);
	// update_hud(board.squareGui->hud, &board.players[0]);

	// int foods[FOODS];
  // for(int i = 0; i < FOODS; i++)
  // {
  //   foods[i] = i;
  // }
	//
	// shuffle(foods, FOODS);
	//
	// for (int i = 0; i < INN_FRAMES; i++) {
	// 	set_food_in_frame(board.squareGui->innGui->foodFrames[i], resources.foods[foods[i]]);
	// 	print_rect(resources.foods[foods[i]]->sprite->rect);
	// }

	load_squares(board.squares, board.playerCount);
	board.squareCount = BOARD_SQUARES;

	for (int i = 1; i < BOARD_SQUARES; i++)
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
}

void board_update()
{
	int scrollX = 0;
	int scrollY = 0;
	int zoom = 0;

	if (board.mode == BM_BOARD)
	{
		const Uint8 *state = SDL_GetKeyboardState(NULL);
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
}

void board_event(SDL_Event* event, SDL_Point* mousePos)
{
	switch (event->type)
	{
		case SDL_MOUSEMOTION:
			board_mouse(mousePos, SDL_FALSE);
			break;
		case SDL_MOUSEBUTTONDOWN:
			board_mouse(mousePos, SDL_TRUE);
			break;
		case SDL_KEYDOWN:
			switch (event->key.keysym.sym)
			{
				case SDLK_RETURN:
					if (board.mode == BM_BOARD)
						random_move();
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
			AnchorInfo ai = board.players[i].traveler.sprite.ai;
			camera_ai(&ai, board.camera);
			rect = anchored_rect(ai, NULL);
			if (SDL_PointInRect(mousePos, &rect) && board.players[i].state != STATE_DISABLED)
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
		for (int position = 0; position < BOARD_SQUARES; position++) {
			AnchorInfo ai = board.squares[position].type.sprite.ai;
			camera_ai(&ai, board.camera);
			rect = anchored_rect(ai, NULL);
			if (SDL_PointInRect(mousePos, &rect)  && board.squares[position].state != STATE_DISABLED)
			{
				if (click)
				{
					board.squares[position].state = STATE_CLICKED;
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
		// if (SDL_PointInRect(mousePos, board.squareGui->res->backBtn->bg->rect) && !board.squareGui->res->backBtn->clicked)
		// {
		// 	if (click)
		// 	{
		// 		board.squareGui->res->backBtn->clicked = 10;
		// 		board.mode = BM_BOARD;
		// 	}
		// 	board.squareGui->res->backBtn->hovered = SDL_TRUE;
		// }
		// else
		// {
		// 	board.squareGui->res->backBtn->hovered = SDL_FALSE;
		// }

		// switch (board.squareId) {
		// 	case SQUARE_INN:
		// 		for (int i = 0; i < INN_FRAMES; i++)
		// 		{
		// 			if (SDL_PointInRect(mousePos, board.squareGui->innGui->foodFrames[i]->frameRect) && !board.squareGui->innGui->foodFrames[i]->clicked)
		// 			{
		// 				if (click)
		// 				{
		// 					board.squareGui->innGui->foodFrames[i]->clicked = 10;
		//
		// 				}
		// 				board.squareGui->innGui->foodFrames[i]->hovered = SDL_TRUE;
		// 			}
		// 			else
		// 			{
		// 				board.squareGui->innGui->foodFrames[i]->hovered = SDL_FALSE;
		// 			}
		// 		}
		// 		break;
		// 	case SQUARE_SHOP:
		// 		for (int i = 0; i < SHOP_FRAMES; i++)
		// 		{
		// 			if (SDL_PointInRect(mousePos, board.squareGui->shopGui->itemFrames[i]->frameRect) && !board.squareGui->shopGui->itemFrames[i]->clicked)
		// 			{
		// 				if (click)
		// 				{
		// 					board.squareGui->shopGui->itemFrames[i]->clicked = 10;
		//
		// 				}
		// 				board.squareGui->shopGui->itemFrames[i]->hovered = SDL_TRUE;
		// 			}
		// 			else
		// 			{
		// 				board.squareGui->shopGui->itemFrames[i]->hovered = SDL_FALSE;
		// 			}
		// 		}
		// 		break;
		// }
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
	for (int i = 0; i < TRAVELERS; i++) {
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
			// SDL_RenderFillRect(renderer, &rect);
		}
	}
}

void draw_squares(Board* board)
{
	for (int position = 0; position < board->squareCount; position++)
	{
		if (board->squares[position].state == STATE_CLICKED)
		{
			SDL_SetTextureColorMod(board->squares[position].type.sprite.tex, 150, 150, 150);
		}
		else if (board->squares[position].state == STATE_HOVERED)
			SDL_SetTextureColorMod(board->squares[position].type.sprite.tex, 200, 200, 200);
		camera_draw_sprite(&board->squares[position].type.sprite, board->camera);
		SDL_SetTextureColorMod(board->squares[position].type.sprite.tex, 255, 255, 255);
	}
}

void draw_players()
{
	// SDL_Rect rect;
	AnchorInfo ai;
	for (int i = 0; i < board.playerCount; i++)
	{
		if (board.players[i].state == STATE_HOVERED)
			SDL_SetTextureColorMod(board.players[i].traveler.sprite.tex, 200, 200, 200);
		camera_draw_sprite(&board.players[i].traveler.sprite, board.camera);
		SDL_SetTextureColorMod(board.players[i].traveler.sprite.tex, 255, 255, 255);
	}
	for (int i = 0; i < board.playerCount; i++)
	{
		if (board.players[i].state == STATE_HOVERED)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
			SDL_Rect rect = anchored_rect(ai, NULL);
			SDL_RenderFillRect(renderer, &rect);
			draw_sprite(board.players[i].nameTag->sprite);
		}
	}
}

void draw_hud(Hud* hud)
{
	SDL_Rect rect = {0, 0, WINDOW_WIDTH, 70};
	SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
	SDL_RenderFillRect(renderer, &rect);

	// draw_sprite(board.squareGui->hud->travelerIcon);
	// draw_sprite(board.squareGui->hud->nick);
	//
	// draw_sprite(board.squareGui->hud->coinIcon);
	// draw_sprite(board.squareGui->hud->coinText->sprite);
	//
	// draw_sprite(board.squareGui->hud->bundleTkIcon);
	// draw_sprite(board.squareGui->hud->bundleTkText->sprite);
	//
	// draw_sprite(board.squareGui->hud->templeCoinIcon);
	// draw_sprite(board.squareGui->hud->templeCoinText->sprite);

}

void draw_board()
{
	// draw_char_sel_gui();
	if (board.mode == BM_SQUARE)
	{

	}
	else if (board.mode == BM_BOARD)
	{
		// draw_bg(); // Affiche l'arrière plan du plateau
		draw_lines(board.squareCount);
		draw_squares(&board);
		draw_players();
		// draw_points();
	}
	// draw_hud();
}

int whos_turn_is_it()
{
	int minPos = BOARD_SQUARES;
	int maxRoadDist = -1;
	int playerId;
	for (int i = 0; i < board.playerCount; i++) {
		if (board.players[i].position < minPos)
			minPos = board.players[i].position;
	}
	for (int i = 0; i < board.playerCount; i++) {
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

	for (int i = 0; i < board.playerCount; i++) {
		if (board.players[i].position == position)
			space--;
	}
	if (space <= 0)
		return SDL_FALSE;

	if ((board.squares[position].type.id == SQUARE_SHOP || board.squares[position].type.id == SQUARE_TEMPLE) && player.coins == 0)
		return SDL_FALSE;
	return SDL_TRUE;
}

void random_move()
{
	int playerId = whos_turn_is_it();
	int possibleSquares[5];
	int possibilities = 0;
	for (int position = board.players[playerId].position + 1; position < BOARD_SQUARES; position++)
	{

		if (is_move_allowed(position, board.players[playerId]))
		{
			possibleSquares[possibilities] = position;
			possibilities++;
		}
		if (possibilities == 5)
			break;
	}
	if (possibilities == 0)
	{
		printf("\e[34m [DEBUG] Game over !\e[37m\n");
		return;
	}
	shuffle(possibleSquares, possibilities);
	int position = possibleSquares[0];
	int space = board.squares[position].capacity;
	for (int i = 0; i < board.playerCount; i++) {
		if (board.players[i].position == position)
			space--;
	}
	board.players[playerId].position = position;
	board.players[playerId].roadDist = board.squares[position].capacity - space;
	update_player_ai(&board.players[playerId]);
	// printf("new pos : %d %d\n", position, board.players[playerId].roadDist);
	return;
}

void square_action(Square* square)
{
	Player* player = &board.players[whos_turn_is_it()];
	printf("SQUARE ACTION = %s\n", player->nickname);
	// switch (square->type.id)
	// {
	// 	board.squareId = SQUARE_INN;
	//
	// 	case SQUARE_INN:
	// 		printf("TYPE = INN\n");
	// 		break;
	// 	case SQUARE_SHOP:
	// 		board.squareId = SQUARE_SHOP;
	// 		printf("TYPE = SHOP\n");
	// 		int items[ITEMS];
	// 	  for(int i = 0; i < ITEMS; i++)
	// 	  {
	// 	    items[i] = i;
	// 	  }
	// 		shuffle(items, ITEMS);
	// 		for (int i = 0; i < SHOP_FRAMES; i++) {
	// 			// set_item_in_frame(board.squareGui->shopGui->itemFrames[i], resources.items[items[i]]);
	// 		}
	// 		break;
	// 	case SQUARE_HOTSPRING:
	// 		board.squareId = SQUARE_HOTSPRING;
	// 		printf("TYPE = HOTSPRING\n");
	// 		// sprintf(board.squareGui->hotSpringGui->obtained.content, "Vous avez obtenu %d points de victoire.", init_hotspring());
	// 		// update_text(board.squareGui->hotSpringGui->obtained);
	// 		break;
	// 	case SQUARE_FARM:
	// 		board.squareId = SQUARE_FARM;
	// 		printf("TYPE = FARM\n");
	// 		break;
	// }
}
