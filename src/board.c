#include <board.h>

Board board;
Ressources ressources;

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

	for (int i = 0; i < BOARD_SQUARES; i++)
	{
		squares[i].type = ressources.squareTypes[boardSquares[i]];
		squares[i].capacity = boardCapacities[i];
	}
}

void init_board(Account* loggedAccount)
{
	srand(time(NULL));

	board.camera.origin.x = 0;
	board.camera.origin.y = 0;
	board.camera.scale = 1.f;

	board.squareGui = init_square_gui(loggedAccount->nick);

	int foods[FOODS];
  for(int i = 0; i < FOODS; i++)
  {
    foods[i] = i;
  }

	shuffle(foods, FOODS);

	for (int i = 0; i < INN_FRAMES; i++) {
		set_food_in_frame(board.squareGui->innGui->foodFrames[i], ressources.foods[foods[i]]);
		// print_rect(ressources.foods[foods[i]]->sprite->rect);
	}

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


	for (int i = 0; i < BOARD_PLAYERS; i++)
	{
		board.players[i].traveler = ressources.travelers[travId[i]];
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
		board.players[i].nameTag = new_sprite_from_str(board.players[i].nickname, 0, 0, 0, 0.5);
		board.players[i].position = 0;
		board.players[i].roadDist = roadDist[i];
		board.players[i].bundleToken = 0;
		board.players[i].coins = board.players[i].traveler->startCoins;
		board.players[i].templeCoins = 0;
		board.players[i].hotSpring = 0;
		board.players[i].foodCount = 0;
		board.players[i].itemCount = 0;
		board.players[i].encounterCount = 0;
		board.players[i].panRice = 0;
		board.players[i].panMount = 0;
		board.players[i].panSea = 0;
		// printf(" %s\n", board.players[i].nickname);
		// printf(" \e[32m%s\e[37m\n\n", ressources.travelers[board.players[i].traveler].name);
		board.playerCount++;
	}

	load_squares(board.squares, board.playerCount);
	board.squareCount = BOARD_SQUARES;

	board.squares[0].offsetY = 0;
	for (int i = 1; i < BOARD_SQUARES; i++)
	{
		board.squares[i].offsetY = board.squares[i - 1].offsetY + (rand() % 150 - 75);
		board.squares[i].hovered = SDL_FALSE;
		board.squares[i].clicked = 0;
		board.squares[i].position = i;
	}
}

void hover_board(SDL_Point* mousePos)
{
	SDL_Rect rect;

	for (int position = 0; position < BOARD_SQUARES; position++) {
		rect.x = board.camera.scale * (board.camera.origin.x + 128 * position);
		rect.y = board.camera.scale * (board.squares[position].offsetY + board.camera.origin.y + WINDOW_HEIGHT - 100 - 128/2);
		rect.w = board.camera.scale * 128;
		rect.h = board.camera.scale * 128;
		if (SDL_PointInRect(mousePos, &rect))
			board.squares[position].hovered = SDL_TRUE;
		else
			board.squares[position].hovered = SDL_FALSE;
	}
}

void click_board(SDL_Point* mousePos)
{
	SDL_Rect rect;

	for (int position = 0; position < BOARD_SQUARES; position++) {
		rect.x = board.camera.scale * (board.camera.origin.x + 128 * position);
		rect.y = board.camera.scale * (board.squares[position].offsetY + board.camera.origin.y + WINDOW_HEIGHT - 100 - 128/2);
		rect.w = board.camera.scale * 128;
		rect.h = board.camera.scale * 128;
		if (SDL_PointInRect(mousePos, &rect))
		{
			board.squares[position].clicked = 10;
			square_action(&board.squares[position]);
		}
	}
}

void draw_bg(void)
{

}

void draw_lines(int squareCount)
{
	SDL_Rect rect;
	if (!squareCount)
		return;

	for (int position = 0; position < squareCount - 1; position++)
	{
		SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
		rect.x = board.camera.scale * (board.camera.origin.x + 128 * position + 128/2);
		rect.y = board.camera.scale * (board.squares[position].offsetY + board.camera.origin.y + WINDOW_HEIGHT - 100 - 2);
		rect.w = board.camera.scale * 128;
		rect.h = board.camera.scale * 4;
		for (int j = 0; j <= (int)(board.camera.scale * 4); j++)
		{
			SDL_RenderDrawLine(renderer, rect.x, rect.y + j, rect.x + rect.w, board.camera.scale * (board.squares[position + 1].offsetY + board.camera.origin.y + WINDOW_HEIGHT - 100 - 2) + j);
		}
		// SDL_RenderFillRect(renderer, &rect);
	}

	for (int position = 0; position < squareCount; position++)
	{
		for (int j = 0; j < board.squares[position].capacity; j++)
		{
			SDL_SetRenderDrawColor(renderer, board.squares[position].type->color.r, board.squares[position].type->color.g, board.squares[position].type->color.b, 255);

			rect.x = board.camera.scale * (board.camera.origin.x + 128 * position + 128/2 - 2);
			rect.y = board.camera.scale * (board.squares[position].offsetY + board.camera.origin.y + WINDOW_HEIGHT - 100 - 128 * j - 128);
			// if (position%2)
			// 	rect.y = WINDOW_HEIGHT - 100 + 128 * j;
			rect.w = board.camera.scale * 4;
			rect.h = board.camera.scale * 128;
			if (is_rect_on_screen(&rect))
			{
				SDL_RenderFillRect(renderer, &rect);
			}

			rect.x = board.camera.scale * (board.camera.origin.x + 128 * position + 128/2 - 10);
			rect.y = board.camera.scale * (board.squares[position].offsetY + board.camera.origin.y + WINDOW_HEIGHT - 100 - 128 * j - 128 - 10);
			// if (position%2)
			// 	rect.y = WINDOW_HEIGHT - 100 + 128 * j + 128;
			rect.w = board.camera.scale * 20;
			rect.h = board.camera.scale * 20;
			SDL_SetTextureColorMod(board.squares[position].type->sprite->tex, board.squares[position].type->color.r, board.squares[position].type->color.g, board.squares[position].type->color.b);
			if (is_rect_on_screen(&rect))
			{
				SDL_RenderCopy(renderer, ressources.squareTypes[9]->sprite->tex, ressources.squareTypes[9]->sprite->texPos, &rect);
			}
			SDL_SetTextureColorMod(board.squares[position].type->sprite->tex, 255, 255, 255);
			// SDL_RenderFillRect(renderer, &rect);
		}
	}
}

void draw_squares(Board* board)
{
	SDL_Rect rect;
	for (int position = 0; position < board->squareCount; position++)
	{
		rect.x = board->camera.scale * (board->camera.origin.x + 128 * position);
		rect.y = board->camera.scale * (board->squares[position].offsetY + board->camera.origin.y + WINDOW_HEIGHT - 100 - 128/2);
		rect.w = board->camera.scale * 128;
		rect.h = board->camera.scale * 128;
		if (is_rect_on_screen(&rect))
		{
			if (board->squares[position].clicked)
			{
				SDL_SetTextureColorMod(board->squares[position].type->sprite->tex, 150, 150, 150);
				board->squares[position].clicked--;
			}
			else if (board->squares[position].hovered)
				SDL_SetTextureColorMod(board->squares[position].type->sprite->tex, 200, 200, 200);
			SDL_RenderCopy(renderer, board->squares[position].type->sprite->tex, board->squares[position].type->sprite->texPos, &rect);
			SDL_SetTextureColorMod(board->squares[position].type->sprite->tex, 255, 255, 255);
		}
	}
}

void draw_players()
{
	SDL_Rect rect;
	for (int i = 0; i < board.playerCount; i++) {
		rect.x = board.camera.scale * (board.camera.origin.x + 128 * board.players[i].position + 128/2 - 100/2);
		rect.y = board.camera.scale * (board.squares[board.players[i].position].offsetY + board.camera.origin.y + WINDOW_HEIGHT - 100 - 128 * (board.players[i].roadDist + 1) - 100/2);
		rect.w = board.camera.scale * 100;
		rect.h = board.camera.scale * 100;
		center_rect(board.players[i].nameTag->rect, new_rect(rect.x - board.players[i].nameTag->rect->w, rect.y, board.players[i].nameTag->rect->w, rect.h));
		draw_sprite(board.players[i].nameTag);
		if (is_rect_on_screen(&rect))
		{
			SDL_RenderCopy(renderer, board.players[i].traveler->sprite->tex, board.players[i].traveler->sprite->texPos, &rect);
		}
	}
}

void draw_hud()
{
	SDL_Rect rect = {0, 0, WINDOW_WIDTH, 64};
	SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
	SDL_RenderFillRect(renderer, &rect);
	draw_sprite(board.squareGui->hud->nick);
}

void draw_board()
{
	// draw_inn(board.squareGui->innGui);
	// draw_bg(); // Affiche l'arrière plan du plateau
	draw_lines(board.squareCount);
	// draw_points();
	draw_squares(&board);
	draw_players();
	draw_hud();
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
	// printf("Next move : %s\n", ressources.travelers[board.players[playerId].traveler].name);
	return playerId;
}

SDL_bool is_move_allowed(int position, Player player)
{
	int next_inn;
	int space = board.squares[position].capacity;

	for (int i = player.position + 1; i < BOARD_SQUARES; i++)
	{

		if (board.squares[i].type->id == SQUARE_INN)
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

	if ((board.squares[position].type->id == SQUARE_SHOP || board.squares[position].type->id == SQUARE_TEMPLE) && player.coins == 0)
		return SDL_FALSE;
	return SDL_TRUE;
}

void random_move()
{
	int playerId = whos_turn_is_it();
	int possibleSquares[BOARD_SQUARES];
	int possibilities = 0;
	for (int position = board.players[playerId].position + 1; position < BOARD_SQUARES; position++)
	{

		if (is_move_allowed(position, board.players[playerId]))
		{
			possibleSquares[possibilities] = position;
			possibilities++;
			// printf("Possible square : %d\n", position);
		}
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
	// printf("new pos : %d %d\n", position, board.players[playerId].roadDist);
	return;
}

void square_action(Square* square)
{
	Player* player = &board.players[whos_turn_is_it()];
	printf("SQUARE ACTION = %s\n", player->nickname);
	switch (square->type->id)
	{
		case SQUARE_INN:
			printf("TYPE = INN\n");
			break;
	}
}
