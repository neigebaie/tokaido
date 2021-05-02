#include <game.h>

int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

int tk_from_collection(Item newItem, Item* items, int itemCount)
{
	int lastTk = 0;
	int newTk  = 0;
	int categorieQt[] = {0, 0, 0, 0};
	for (int i = 0; i < itemCount; i++)
	{
		categorieQt[items[i].category.id]++;
	}
	qsort(categorieQt, 4, sizeof(int), cmpfunc);
	lastTk += categorieQt[3] * 1;
	lastTk += categorieQt[2] * 3;
	lastTk += categorieQt[1] * 5;
	lastTk += categorieQt[0] * 7;

	categorieQt[newItem.category.id]++;
	qsort(categorieQt, 4, sizeof(int), cmpfunc);
	newTk  += categorieQt[3] * 1;
	newTk  += categorieQt[2] * 3;
	newTk  += categorieQt[1] * 5;
	newTk  += categorieQt[0] * 7;

	return newTk - lastTk;
}

void reset_recap(Recap* recap)
{
	recap->bundleToken = 0;
	recap->coins = 0;
	recap->templeCoins = 0;
	recap->foodCount = 0;
	recap->itemCount = 0;
	recap->encounterCount = 0;
	recap->panRice = 0;
	recap->panMount = 0;
	recap->panSea = 0;
}

void load_resources()
{
	// ITEM CATS

	for (int i = 0 ; i< ITEM_CATS; i++)
	{
		resources.itemCats[i] = (ItemCategory*)malloc(sizeof(ItemCategory));
	}

	strcpy(resources.itemCats[0]->name,  "objet d'art");
	resources.itemCats[0]->id = 0;
	strcpy(resources.itemCats[1]->name,  "nourriture");
	resources.itemCats[1]->id = 1;
	strcpy(resources.itemCats[2]->name,  "accessoire");
	resources.itemCats[2]->id = 2;
	strcpy(resources.itemCats[3]->name,  "vêtement");
	resources.itemCats[3]->id = 3;

	// ITEMS

	for (int i = 0 ; i< ITEMS; i++)
	{
		resources.items[i] = (Item*)malloc(sizeof(Item));
	}

	strcpy(resources.items[0]->name,  "Yunomi");
	strcpy(resources.items[1]->name,  "Konpeito");
	strcpy(resources.items[2]->name,  "Manju");
	strcpy(resources.items[3]->name,  "Kanaboko");
	strcpy(resources.items[4]->name,  "Daifuku");
	strcpy(resources.items[5]->name,  "Gofu");
	strcpy(resources.items[6]->name,  "Koma");
	strcpy(resources.items[7]->name,  "Hashi");
	strcpy(resources.items[8]->name,  "Uchiwa");
	strcpy(resources.items[9]->name,  "Washi");
	strcpy(resources.items[10]->name, "Ucha");
	strcpy(resources.items[11]->name, "Sake");
	strcpy(resources.items[12]->name, "Sandogasa");
	strcpy(resources.items[13]->name, "Yukata");
	strcpy(resources.items[14]->name, "Furoshiki");
	strcpy(resources.items[15]->name, "Geta");
	strcpy(resources.items[16]->name, "Kan Zashi");
	strcpy(resources.items[17]->name, "Haori");
	strcpy(resources.items[18]->name, "Netsuke");
	strcpy(resources.items[19]->name, "Jubako");
	strcpy(resources.items[20]->name, "Shikki");
	strcpy(resources.items[21]->name, "Shamisen");
	strcpy(resources.items[22]->name, "Sumie");
	strcpy(resources.items[23]->name, "Ukiyoe");

	int itemCatsId[] = {2, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0};
	int priceItem[] =  {1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3};
	for (int i = 0; i < ITEMS; i++)
	{
		resources.items[i]->category = *resources.itemCats[itemCatsId[i]];
		resources.items[i]->price = priceItem[i];
		resources.items[i]->sprite = new_sprite(textureMgr->itemTex, new_rect(i * 128, 0, 128, 128));
	}

	// FOODS

	for (int i = 0 ; i < FOODS; i++)
	{
		resources.foods[i] = (Food*)malloc(sizeof(Food));
	}

	strcpy(resources.foods[0]->name,  "Misoshiru");
	strcpy(resources.foods[1]->name,  "Nigirimeshi");
	strcpy(resources.foods[2]->name,  "Dango");
	strcpy(resources.foods[3]->name,  "Yakitori");
	strcpy(resources.foods[4]->name,  "Soba");
	strcpy(resources.foods[5]->name,  "Sushi");
	strcpy(resources.foods[6]->name,  "Tofu");
	strcpy(resources.foods[7]->name,  "Tempura");
	strcpy(resources.foods[8]->name,  "Unagi");
	strcpy(resources.foods[9]->name,  "Donburi");
	strcpy(resources.foods[10]->name, "Udon");
	strcpy(resources.foods[11]->name, "Fugu");
	strcpy(resources.foods[12]->name, "Tai Meshi");
	strcpy(resources.foods[13]->name, "Sashimi");

	int priceFood[] = {1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3};
	for (int i = 0; i < FOODS; i++)
	{
		resources.foods[i]->price = priceFood[i];
		resources.foods[i]->sprite = (Sprite*)malloc(sizeof(Sprite));
		resources.foods[i]->sprite->tex = textureMgr->foodTex;
		resources.foods[i]->sprite->crop = (SDL_Rect*)malloc(sizeof(SDL_Rect));
		resources.foods[i]->sprite->crop->x = i * 128;
		resources.foods[i]->sprite->crop->y = 0;
		resources.foods[i]->sprite->crop->w = 128;
		resources.foods[i]->sprite->crop->h = 128;
		resources.foods[i]->sprite->ai.size.w = 128;
		resources.foods[i]->sprite->ai.size.h = 128;
	}

	// ENCOUNTERS

	for (int i = 0 ; i< ENCOUNTERS; i++)
	{
		resources.encounters[i] = (Encounter*)malloc(sizeof(Encounter));
	}

	strcpy(resources.encounters[0]->name,  "Annaibito"); // Rizière
	strcpy(resources.encounters[1]->name,  "Annaibito"); // Montagne
	strcpy(resources.encounters[2]->name,  "Annaibito"); // Mer
	strcpy(resources.encounters[3]->name,  "Shokunin");
	strcpy(resources.encounters[4]->name,  "Miko");
	strcpy(resources.encounters[5]->name,  "Kuge");
	strcpy(resources.encounters[6]->name,  "Samourai");


	// TRAVELERS

	for (int i = 0 ; i< TRAVELERS; i++)
	{
		resources.travelers[i] = (Traveler*)malloc(sizeof(Traveler));
	}

	strcpy(resources.travelers[0]->name,  "Satsuki");
	resources.travelers[0]->id = TRAVELER_SATSUKI;
	strcpy(resources.travelers[1]->name,  "Hiroshige");
	resources.travelers[1]->id = TRAVELER_HIROSHIGE;
	strcpy(resources.travelers[2]->name,  "Chuubei");
	resources.travelers[2]->id = TRAVELER_CHUUBEI;
	strcpy(resources.travelers[3]->name,  "Mitsukuni");
	resources.travelers[3]->id = TRAVELER_MITSUKUNI;
	strcpy(resources.travelers[4]->name,  "Sasayakko");
	resources.travelers[4]->id = TRAVELER_SASAYAKKO;
	strcpy(resources.travelers[5]->name,  "Umegae");
	resources.travelers[5]->id = TRAVELER_UMEGAE;
	strcpy(resources.travelers[6]->name,  "Kinko");
	resources.travelers[6]->id = TRAVELER_KINKO;
	strcpy(resources.travelers[7]->name,  "Hirotada");
	resources.travelers[7]->id = TRAVELER_HIROTADA;
	strcpy(resources.travelers[8]->name,  "Zen-emon");
	resources.travelers[8]->id = TRAVELER_ZEN_EMON;
	strcpy(resources.travelers[9]->name,  "Yoshiyasu");
	resources.travelers[9]->id = TRAVELER_YOSHIYASU;

	int startCoins[] = {2, 3, 4, 6, 5, 5, 7, 8, 6, 9};
	for (int i = 0; i < TRAVELERS; i++)
	{
		resources.travelers[i]->startCoins = startCoins[i];
		resources.travelers[i]->sprite = *new_sprite(textureMgr->travelerTex, new_rect(i * 256, 0, 256, 256));
		resources.travelers[i]->sprite.ai.size.w *= 0.85;
		resources.travelers[i]->sprite.ai.size.h *= 0.85;
	}


	// SQUARE TYPES

	for (int i = 0 ; i< SQUARES; i++)
	{
		resources.squareTypes[i] = (SquareType*)malloc(sizeof(SquareType));
	}

	strcpy(resources.squareTypes[0]->name,  "Relai");
	resources.squareTypes[0]->color.r = (float)56/(float)100 * 255;
	resources.squareTypes[0]->color.g = (float)13/(float)100 * 255;
	resources.squareTypes[0]->color.b = (float)7/(float)100 * 255;

	strcpy(resources.squareTypes[1]->name,  "Échoppe");
	resources.squareTypes[1]->color.r = (float)5/(float)100 * 255;
	resources.squareTypes[1]->color.g = (float)5/(float)100 * 255;
	resources.squareTypes[1]->color.b = (float)5/(float)100 * 255;

	strcpy(resources.squareTypes[2]->name,  "Source Chaude");
	resources.squareTypes[2]->color.r = (float)40/(float)100 * 255;
	resources.squareTypes[2]->color.g = (float)76/(float)100 * 255;
	resources.squareTypes[2]->color.b = (float)79/(float)100 * 255;

	strcpy(resources.squareTypes[3]->name,  "Temple");
	resources.squareTypes[3]->color.r = (float)75/(float)100 * 255;
	resources.squareTypes[3]->color.g = (float)17/(float)100 * 255;
	resources.squareTypes[3]->color.b = (float)13/(float)100 * 255;

	strcpy(resources.squareTypes[4]->name,  "Rencontre");
	resources.squareTypes[4]->color.r = (float)86/(float)100 * 255;
	resources.squareTypes[4]->color.g = (float)54/(float)100 * 255;
	resources.squareTypes[4]->color.b = (float)71/(float)100 * 255;

	strcpy(resources.squareTypes[5]->name,  "Ferme");
	resources.squareTypes[5]->color.r = (float)75/(float)100 * 255;
	resources.squareTypes[5]->color.g = (float)53/(float)100 * 255;
	resources.squareTypes[5]->color.b = (float)11/(float)100 * 255;

	strcpy(resources.squareTypes[6]->name,  "Panorama Rizière");
	resources.squareTypes[6]->color.r = (float)51/(float)100 * 255;
	resources.squareTypes[6]->color.g = (float)66/(float)100 * 255;
	resources.squareTypes[6]->color.b = (float)27/(float)100 * 255;

	strcpy(resources.squareTypes[7]->name,  "Panorama Montagne");
	resources.squareTypes[7]->color.r = (float)74/(float)100 * 255;
	resources.squareTypes[7]->color.g = (float)80/(float)100 * 255;
	resources.squareTypes[7]->color.b = (float)80/(float)100 * 255;

	strcpy(resources.squareTypes[8]->name,  "Panorama Mer");
	resources.squareTypes[8]->color.r = (float)30/(float)100 * 255;
	resources.squareTypes[8]->color.g = (float)58/(float)100 * 255;
	resources.squareTypes[8]->color.b = (float)75/(float)100 * 255;

	strcpy(resources.squareTypes[9]->name,  "Point");
	resources.squareTypes[9]->color.r = 255;
	resources.squareTypes[9]->color.g = 255;
	resources.squareTypes[9]->color.b = 255;

	for (int i = 0; i < SQUARES; i++)
	{
		resources.squareTypes[i]->id = i;
		resources.squareTypes[i]->sprite = *new_sprite(textureMgr->squareTex, new_rect(i * 256, 0, 256, 256));
		// resources.squareTypes[i]->sprite->ai.size.w *= 0.85;
		// resources.squareTypes[i]->sprite->ai.size.h *= 0.85;
	}

	printf("\e[34m [DEBUG] Game resources loaded !\e[37m\n");
}
