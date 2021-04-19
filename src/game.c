#include <game.h>

void load_ressources(void)
{
	// TEXTURES

	SDL_Texture* squareTex = load_texture("ressources/gfx/square_spritesheet.png");
	SDL_Texture* foodTex = load_texture("ressources/gfx/food_spritesheet.png");
	SDL_Texture* travelerTex = load_texture("ressources/gfx/traveler_spritesheet.png");
	// SDL_Texture* itemTex = load_texture("ressources/gfx/item_spritesheet.png");
	// SDL_Texture* encounterTex = load_texture("ressources/gfx/encounter_spritesheet.png");


	// ITEMS

	for (int i = 0 ; i< ITEMS; i++)
	{
		ressources.items[i] = (Item*)malloc(sizeof(Item));
	}

	strcpy(ressources.items[0]->name,  "Yunomi");
	strcpy(ressources.items[1]->name,  "Konpeito");
	strcpy(ressources.items[2]->name,  "Manju");
	strcpy(ressources.items[3]->name,  "Kanaboko");
	strcpy(ressources.items[4]->name,  "Daifuku");
	strcpy(ressources.items[5]->name,  "Gofu");
	strcpy(ressources.items[6]->name,  "Koma");
	strcpy(ressources.items[7]->name,  "Hashi");
	strcpy(ressources.items[8]->name,  "Uchiwa");
	strcpy(ressources.items[9]->name,  "Washi");
	strcpy(ressources.items[10]->name, "Ucha");
	strcpy(ressources.items[11]->name, "Sake");
	strcpy(ressources.items[12]->name, "Sandogasa");
	strcpy(ressources.items[13]->name, "Yukata");
	strcpy(ressources.items[14]->name, "Furoshiki");
	strcpy(ressources.items[15]->name, "Geta");
	strcpy(ressources.items[16]->name, "Kan Zashi");
	strcpy(ressources.items[17]->name, "Haori");
	strcpy(ressources.items[18]->name, "Netsuke");
	strcpy(ressources.items[19]->name, "Jubako");
	strcpy(ressources.items[20]->name, "Shikki");
	strcpy(ressources.items[21]->name, "Shamisen");
	strcpy(ressources.items[22]->name, "Sumie");
	strcpy(ressources.items[23]->name, "Ukiyoe");


	// FOODS

	for (int i = 0 ; i< FOODS; i++)
	{
		ressources.foods[i] = (Food*)malloc(sizeof(Food));
	}

	strcpy(ressources.foods[0]->name,  "Misoshiru");
	strcpy(ressources.foods[1]->name,  "Nigirimeshi");
	strcpy(ressources.foods[2]->name,  "Dango");
	strcpy(ressources.foods[3]->name,  "Yakitori");
	strcpy(ressources.foods[4]->name,  "Soba");
	strcpy(ressources.foods[5]->name,  "Sushi");
	strcpy(ressources.foods[6]->name,  "Tofu");
	strcpy(ressources.foods[7]->name,  "Tempura");
	strcpy(ressources.foods[8]->name,  "Unagi");
	strcpy(ressources.foods[9]->name,  "Donburi");
	strcpy(ressources.foods[10]->name, "Udon");
	strcpy(ressources.foods[11]->name, "Fugu");
	strcpy(ressources.foods[12]->name, "Tai Meshi");
	strcpy(ressources.foods[13]->name, "Sashimi");

	for (int i = 0; i < FOODS; i++)
	{
		ressources.foods[i]->sprite = (Sprite*)malloc(sizeof(Sprite));
		ressources.foods[i]->sprite->tex = foodTex;
		ressources.foods[i]->sprite->texPos = (SDL_Rect*)malloc(sizeof(SDL_Rect));
		ressources.foods[i]->sprite->texPos->x = i * 126;
		ressources.foods[i]->sprite->texPos->y = 0;
		ressources.foods[i]->sprite->texPos->w = 126;
		ressources.foods[i]->sprite->texPos->h = 115;
		ressources.foods[i]->sprite->rect = new_rect(0, 0, 126, 115);
	}

	// ENCOUNTERS

	for (int i = 0 ; i< ENCOUNTERS; i++)
	{
		ressources.encounters[i] = (Encounter*)malloc(sizeof(Encounter));
	}

	strcpy(ressources.encounters[0]->name,  "Annaibito"); // Rizière
	strcpy(ressources.encounters[1]->name,  "Annaibito"); // Montagne
	strcpy(ressources.encounters[2]->name,  "Annaibito"); // Mer
	strcpy(ressources.encounters[3]->name,  "Shokunin");
	strcpy(ressources.encounters[4]->name,  "Miko");
	strcpy(ressources.encounters[5]->name,  "Kuge");
	strcpy(ressources.encounters[6]->name,  "Samourai");


	// TRAVELERS

	for (int i = 0 ; i< TRAVELERS; i++)
	{
		ressources.travelers[i] = (Traveler*)malloc(sizeof(Traveler));
	}

	strcpy(ressources.travelers[0]->name,  "Satsuki");
	ressources.travelers[0]->startCoins = 2;

	strcpy(ressources.travelers[1]->name,  "Hiroshige");
	ressources.travelers[1]->startCoins = 3;

	strcpy(ressources.travelers[2]->name,  "Chuubei");
	ressources.travelers[2]->startCoins = 4;

	strcpy(ressources.travelers[3]->name,  "Mitsukuni");
	ressources.travelers[3]->startCoins = 6;

	strcpy(ressources.travelers[4]->name,  "Sasayakko");
	ressources.travelers[4]->startCoins = 5;

	strcpy(ressources.travelers[5]->name,  "Umegae");
	ressources.travelers[5]->startCoins = 5;

	strcpy(ressources.travelers[6]->name,  "Kinko");
	ressources.travelers[6]->startCoins = 7;

	strcpy(ressources.travelers[7]->name,  "Hirotada");
	ressources.travelers[7]->startCoins = 8;

	strcpy(ressources.travelers[8]->name,  "Len-emon");
	ressources.travelers[8]->startCoins = 6;

	strcpy(ressources.travelers[9]->name,  "Yoshiyasu");
	ressources.travelers[9]->startCoins = 9;

	// strcpy(ressources.travelers[10]->name,  "Unknown");
	// ressources.travelers[10]->startCoins = 2;

	for (int i = 0; i < TRAVELERS; i++)
	{
		ressources.travelers[i]->sprite = (Sprite*)malloc(sizeof(Sprite));
		ressources.travelers[i]->sprite->tex = travelerTex;
		ressources.travelers[i]->sprite->texPos = (SDL_Rect*)malloc(sizeof(SDL_Rect));
		ressources.travelers[i]->sprite->texPos->x = i * 256;
		ressources.travelers[i]->sprite->texPos->y = 0;
		ressources.travelers[i]->sprite->texPos->w = 256;
		ressources.travelers[i]->sprite->texPos->h = 256;
	}


	// SQUARE TYPES

	for (int i = 0 ; i< SQUARES; i++)
	{
		ressources.squareTypes[i] = (SquareType*)malloc(sizeof(SquareType));
	}

	strcpy(ressources.squareTypes[0]->name,  "Relai");
	ressources.squareTypes[0]->color.r = (float)56/(float)100 * 255;
	ressources.squareTypes[0]->color.g = (float)13/(float)100 * 255;
	ressources.squareTypes[0]->color.b = (float)7/(float)100 * 255;

	strcpy(ressources.squareTypes[1]->name,  "Échoppe");
	ressources.squareTypes[1]->color.r = (float)5/(float)100 * 255;
	ressources.squareTypes[1]->color.g = (float)5/(float)100 * 255;
	ressources.squareTypes[1]->color.b = (float)5/(float)100 * 255;

	strcpy(ressources.squareTypes[2]->name,  "Source Chaude");
	ressources.squareTypes[2]->color.r = (float)40/(float)100 * 255;
	ressources.squareTypes[2]->color.g = (float)76/(float)100 * 255;
	ressources.squareTypes[2]->color.b = (float)79/(float)100 * 255;

	strcpy(ressources.squareTypes[3]->name,  "Temple");
	ressources.squareTypes[3]->color.r = (float)75/(float)100 * 255;
	ressources.squareTypes[3]->color.g = (float)17/(float)100 * 255;
	ressources.squareTypes[3]->color.b = (float)13/(float)100 * 255;

	strcpy(ressources.squareTypes[4]->name,  "Rencontre");
	ressources.squareTypes[4]->color.r = (float)86/(float)100 * 255;
	ressources.squareTypes[4]->color.g = (float)54/(float)100 * 255;
	ressources.squareTypes[4]->color.b = (float)71/(float)100 * 255;

	strcpy(ressources.squareTypes[5]->name,  "Ferme");
	ressources.squareTypes[5]->color.r = (float)75/(float)100 * 255;
	ressources.squareTypes[5]->color.g = (float)53/(float)100 * 255;
	ressources.squareTypes[5]->color.b = (float)11/(float)100 * 255;

	strcpy(ressources.squareTypes[6]->name,  "Panorama Rizière");
	ressources.squareTypes[6]->color.r = (float)51/(float)100 * 255;
	ressources.squareTypes[6]->color.g = (float)66/(float)100 * 255;
	ressources.squareTypes[6]->color.b = (float)27/(float)100 * 255;

	strcpy(ressources.squareTypes[7]->name,  "Panorama Montagne");
	ressources.squareTypes[7]->color.r = (float)74/(float)100 * 255;
	ressources.squareTypes[7]->color.g = (float)80/(float)100 * 255;
	ressources.squareTypes[7]->color.b = (float)80/(float)100 * 255;

	strcpy(ressources.squareTypes[8]->name,  "Panorama Mer");
	ressources.squareTypes[8]->color.r = (float)30/(float)100 * 255;
	ressources.squareTypes[8]->color.g = (float)58/(float)100 * 255;
	ressources.squareTypes[8]->color.b = (float)75/(float)100 * 255;

	strcpy(ressources.squareTypes[9]->name,  "Point");
	ressources.squareTypes[9]->color.r = 255;
	ressources.squareTypes[9]->color.g = 255;
	ressources.squareTypes[9]->color.b = 255;

	for (int i = 0; i < SQUARES; i++)
	{
		ressources.squareTypes[i]->id = i;
		ressources.squareTypes[i]->sprite = (Sprite*)malloc(sizeof(Sprite));
		ressources.squareTypes[i]->sprite->tex = squareTex;
		ressources.squareTypes[i]->sprite->texPos = (SDL_Rect*)malloc(sizeof(SDL_Rect));
		ressources.squareTypes[i]->sprite->texPos->x = i * 256;
		ressources.squareTypes[i]->sprite->texPos->y = 0;
		ressources.squareTypes[i]->sprite->texPos->w = 256;
		ressources.squareTypes[i]->sprite->texPos->h = 256;
	}

	printf("\e[34m [DEBUG] Game ressources loaded !\e[37m\n");
}
