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

void load_squares(const char* path, Square *squares)
{
	FILE *file = fopen(path, "r");

	if (file == NULL)
	{
		char errorMsg[100];
		sprintf(errorMsg, "%s n'a pas pu être ouvert", path);
		exit_with_error(errorMsg);
	}

	if(!feof(file))
		fread(squares, sizeof(Square), BOARD_SQUARES, file);
	fclose(file);
}

void load_ressources(void)
{
	sprintf(ressources.squares[0].name,  "Relai");
	sprintf(ressources.squares[1].name,  "Échoppe");
	sprintf(ressources.squares[2].name,  "Source Chaude");
	sprintf(ressources.squares[3].name,  "Temple");
	sprintf(ressources.squares[4].name,  "Rencontre");
	sprintf(ressources.squares[5].name,  "Ferme");
	sprintf(ressources.squares[6].name,  "Panorama Rizière");
	sprintf(ressources.squares[7].name,  "Panorama Montagne");
	sprintf(ressources.squares[8].name,  "Panorama Mer");

	// ressources.squareTex = load_texture("ressources/gfx/square_spritesheet.png");


	sprintf(ressources.items[0].name,  "Yunomi");
	sprintf(ressources.items[1].name,  "Konpeito");
	sprintf(ressources.items[2].name,  "Manju");
	sprintf(ressources.items[3].name,  "Kanaboko");
	sprintf(ressources.items[4].name,  "Daifuku");
	sprintf(ressources.items[5].name,  "Gofu");
	sprintf(ressources.items[6].name,  "Koma");
	sprintf(ressources.items[7].name,  "Hashi");
	sprintf(ressources.items[8].name,  "Uchiwa");
	sprintf(ressources.items[9].name,  "Washi");
	sprintf(ressources.items[10].name, "Ucha");
	sprintf(ressources.items[11].name, "Sake");
	sprintf(ressources.items[12].name, "Sandogasa");
	sprintf(ressources.items[13].name, "Yukata");
	sprintf(ressources.items[14].name, "Furoshiki");
	sprintf(ressources.items[15].name, "Geta");
	sprintf(ressources.items[16].name, "Kan Zashi");
	sprintf(ressources.items[17].name, "Haori");
	sprintf(ressources.items[18].name, "Netsuke");
	sprintf(ressources.items[19].name, "Jubako");
	sprintf(ressources.items[20].name, "Shikki");
	sprintf(ressources.items[21].name, "Shamisen");
	sprintf(ressources.items[22].name, "Sumie");
	sprintf(ressources.items[23].name, "Ukiyoe");

	// ressources.itemTex = load_texture("ressources/gfx/item_spritesheet.png");


	sprintf(ressources.foods[0].name,  "Misoshiru");
	sprintf(ressources.foods[1].name,  "Nigirimeshi");
	sprintf(ressources.foods[2].name,  "Dango");
	sprintf(ressources.foods[3].name,  "Yakitori");
	sprintf(ressources.foods[4].name,  "Soba");
	sprintf(ressources.foods[5].name,  "Sushi");
	sprintf(ressources.foods[6].name,  "Tofu");
	sprintf(ressources.foods[7].name,  "Tempura");
	sprintf(ressources.foods[8].name,  "Unagi");
	sprintf(ressources.foods[9].name,  "Donburi");
	sprintf(ressources.foods[10].name, "Udon");
	sprintf(ressources.foods[11].name, "Fugu");
	sprintf(ressources.foods[12].name, "Tai Meshi");
	sprintf(ressources.foods[13].name, "Sashimi");

	ressources.foodTex = load_texture("ressources/gfx/food_spritesheet.png");


	sprintf(ressources.encounters[0].name,  "Annaibito"); // Rizière
	sprintf(ressources.encounters[1].name,  "Annaibito"); // Montagne
	sprintf(ressources.encounters[2].name,  "Annaibito"); // Mer
	sprintf(ressources.encounters[3].name,  "Shokunin");
	sprintf(ressources.encounters[4].name,  "Miko");
	sprintf(ressources.encounters[5].name,  "Kuge");
	sprintf(ressources.encounters[6].name,  "Samourai");

	// ressources.encounterTex = load_texture("ressources/gfx/encounter_spritesheet.png");


	sprintf(ressources.travelers[0].name,  "Satsuki");
	sprintf(ressources.travelers[1].name,  "Hiroshige");
	sprintf(ressources.travelers[2].name,  "Chuubei");
	sprintf(ressources.travelers[3].name,  "Mitsukuni");
	sprintf(ressources.travelers[4].name,  "Sasayakko");
	sprintf(ressources.travelers[5].name,  "Umegae");
	sprintf(ressources.travelers[6].name,  "Kinko");
	sprintf(ressources.travelers[7].name,  "Hirotada");
	sprintf(ressources.travelers[8].name,  "Len-emon");
	sprintf(ressources.travelers[9].name,  "Yoshiyasu");

	// ressources.travelerTex = load_texture("ressources/gfx/traveler_spritesheet.png");
}

// REMOVE
void draw_test(void)
{
	SDL_Rect srcRect = {0, 0, 126, 115};
	SDL_Rect dstRect = {0, 0, 126, 115};
	for (int id = 0; id < 14; id++)
	{
		srcRect.x = srcRect.w * id;
		dstRect.x = dstRect.w * id + id * 10;
		printf("%s\n", ressources.foods[id].name);
		SDL_RenderCopy(renderer, ressources.itemTex, &srcRect, &dstRect);
	}
}

void init_board(void)
{
	srand(time(NULL));

	// Initialisation des joueurs
	int travId[TRAVELERS];
	for (int i = 0; i < TRAVELERS; i++)
	{
		travId[i] = i;
	}

	shuffle(travId, TRAVELERS);

	for (int i = 0; i < BOARD_PLAYERS; i++)
	{
		board.players[i].traveler = travId[i];
		sprintf(board.players[i].nickname, "Joueur %d", i + 1);
		board.players[i].isHuman = SDL_FALSE;
		board.players[i].position = 0;
		board.players[i].bundleToken = 0;
		board.players[i].coins = ressources.travelers[board.players[i].traveler].startCoins;
		board.players[i].templeCoins = 0;
		board.players[i].hotSpring = 0;
		board.players[i].foodCount = 0;
		board.players[i].itemCount = 0;
		board.players[i].encounterCount = 0;
		board.players[i].panRice = 0;
		board.players[i].panMount = 0;
		board.players[i].panSea = 0;
		printf(" %s\n", board.players[i].nickname);
		printf(" \e[32m%s\e[37m\n\n", ressources.travelers[board.players[i].traveler].name);
		board.playerCount++;
	}

	load_squares("ressources/templates/squares.dat", board.squares);

	for (int i = 0; i < BOARD_SQUARES; i++)
	{
		printf(" \e[32m%s\e[37m : \e[31m%d\e[37m\n", ressources.squares[board.squares[i].id].name, board.squares[i].capacity);
	}
}

void draw_bg(void)
{

}

void draw_board(Board board)
{
	// draw_bg(); // Affiche l'arrière plan du plateau
	draw_squares(board.squareCount, board.squares);
}

void draw_squares(int squareCount, Square squares[])
{
	SDL_Rect rect;
	for (int position = 0; position < squareCount; position++)
	{
		rect.x = (WINDOW_WIDTH / squareCount) * position;
		rect.y = WINDOW_HEIGHT/2;
		// SDL_RenderCopy(renderer, squares[position].texture, NULL, &rect);
	}
}

/*
Liste des fonctions à créer :
 - draw_board
 - draw_squares
 - draw_players
 - move_player(Player player, int position, )
 -
 -
 -
*/
