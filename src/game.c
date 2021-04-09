#include "game.h"

void load_ressources(void)
{
	FILE *file = fopen("ressources/templates/ressources.dat", "r");

	if (file == NULL)
	{
		char errorMsg[100];
		sprintf(errorMsg, "ressources/templates/ressources.dat n'a pas pu être ouvert");
		exit_with_error(errorMsg);
	}

	fread(&ressources, sizeof(Ressources), 1, file);

	fclose(file);

	ressources.squareTex = load_texture("ressources/gfx/square_spritesheet.png");
	// ressources.itemTex = load_texture("ressources/gfx/item_spritesheet.png");
	ressources.foodTex = load_texture("ressources/gfx/food_spritesheet.png");
	// ressources.encounterTex = load_texture("ressources/gfx/encounter_spritesheet.png");
	ressources.travelerTex = load_texture("ressources/gfx/traveler_spritesheet.png");
}
