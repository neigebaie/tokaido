#include "board.h"

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

void init_board(void)
{
	srand(time(NULL));

	board.camera.origin = 0;
	board.camera.scale = 1;

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
		sprintf(board.players[i].nickname, "Joueur %d", i + 1);
		board.players[i].isHuman = SDL_FALSE;
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

	/*
	for (int i = 0; i < BOARD_SQUARES; i++)
	{
		printf(" \e[32m%s\e[37m : \e[31m%d\e[37m\n", ressources.squareTypes[board.squares[i].id].name, board.squares[i].capacity);
	}
	*/
}

void draw_bg(void)
{

}

void draw_lines(int squareCount)
{
	SDL_Rect rect;

	for (int position = 0; position < squareCount; position++)
	{
		for (int j = 0; j < board.squares[position].capacity; j++)
		{
			SDL_SetRenderDrawColor(renderer, board.squares[position].type->color.r, board.squares[position].type->color.g, board.squares[position].type->color.b, 255);

			rect.x = board.camera.origin + 128 * position + 128/2 - 2;
			rect.y = WINDOW_HEIGHT - 100 - 128 * j - 128;
			// if (position%2)
			// 	rect.y = WINDOW_HEIGHT - 100 + 128 * j;
			rect.w = 4;
			rect.h = 128;
			SDL_RenderFillRect(renderer, &rect);

			rect.x = board.camera.origin + 128 * position + 128/2 - 10;
			rect.y = WINDOW_HEIGHT - 100 - 128 * j - 128 - 10;
			// if (position%2)
			// 	rect.y = WINDOW_HEIGHT - 100 + 128 * j + 128;
			rect.w = 20;
			rect.h = 20;
			SDL_SetTextureColorMod(board.squares[position].type->sprite->tex, board.squares[position].type->color.r, board.squares[position].type->color.g, board.squares[position].type->color.b);
			SDL_RenderCopy(renderer, ressources.squareTypes[9]->sprite->tex, ressources.squareTypes[9]->sprite->texPos, &rect);
			SDL_SetTextureColorMod(board.squares[position].type->sprite->tex, 255, 255, 255);
			// SDL_RenderFillRect(renderer, &rect);
		}
		if (position == squareCount - 1) // fin du plateau
			return;

		SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);

		rect.x = board.camera.origin + 128 * position + 128/2;
		rect.y = WINDOW_HEIGHT - 100 - 2;
		rect.w = 128;
		rect.h = 4;
		SDL_RenderFillRect(renderer, &rect);
	}
}

void draw_squares(int squareCount, Square *squares)
{
	SDL_Rect rect;
	for (int position = 0; position < squareCount; position++)
	{
		rect.x = (board.camera.origin + 128 * position);
		rect.y = WINDOW_HEIGHT - 100 - 128/2;
		rect.w = 128;
		rect.h = 128;
		SDL_RenderCopy(renderer, board.squares[position].type->sprite->tex, board.squares[position].type->sprite->texPos, &rect);
	}
}

void draw_players()
{
	SDL_Rect rect;
	for (int i = 0; i < board.playerCount; i++) {
		rect.x = board.camera.origin + 128 * board.players[i].position + 128/2 - 100/2;
		rect.y = WINDOW_HEIGHT - 100 - 128 * board.players[i].roadDist - 128 - 100/2;
		rect.w = 100;
		rect.h = 100;
		SDL_RenderCopy(renderer, board.players[i].traveler->sprite->tex, board.players[i].traveler->sprite->texPos, &rect);
	}
}

void draw_board()
{
	// draw_bg(); // Affiche l'arrière plan du plateau
	draw_lines(board.squareCount);
	// draw_points();
	draw_squares(board.squareCount, board.squares);
	draw_players();
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

void square_action2()
{
	Player player = board.players[whos_turn_is_it()];
	switch (whos_turn_is_it())
	{
	 case 0 :
	 		break;
	case 1 :
	 	 	break;
	case 2 :
			break;
	case 3 :
			break;
  case 4 :
			break;
	case 5 :
			break;
	case 6 :
			break;
	case 7 :
			break;
	case 8 :
			break;
	}
}
/*
Liste des fonctions à créer :
 - move_player(Player player, int position)
 - square action
 - random_move -> IA
 -
 - REMOVE GLOBAL VARIABLES
 - pétales de ceriser :3
*/
