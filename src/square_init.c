#include <square_action.h>

void init_inn(Food** foods)
{
	int ids[FOODS];

  for(int i = 0; i < FOODS; i++)
  {
    ids[i] = i;
  }
	shuffle(ids, FOODS);

	for(int i = 0; i < 6; i++)
	{
		foods[i] = resources.foods[ids[i]];
	}
}

void init_shop(Item** items)
{
	int ids[ITEMS];
	for(int i = 0; i < ITEMS; i++)
	{
		ids[i] = i;
	}
	shuffle(ids, ITEMS);

	for(int i = 0; i < 3; i++)
	{
		items[i] = resources.items[ids[i]];
	}
}

int init_hot_spring()
{
  return 2 + rand() % 2;
}

int init_encounter(Player* player)
{
  int choices[ENCOUNTERS];
  int choiceNb = 4;
  choices[0] = 0;
  choices[1] = 4;
  choices[2] = 5;
  choices[3] = 6;
  for (int i = choiceNb; i < ENCOUNTERS; i++)
  {
		if ((i == 1 && player->panRice < 3) || (i == 2 && player->panMount < 4) || (i == 3 && player->panSea < 5))
    {
      choices[choiceNb] = i;
      choiceNb++;
    }
  }
  shuffle(choices, choiceNb);

  return choices[0];
}
