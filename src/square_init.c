#include "square_action.h"

void init_inn(int* innFoods, int playerCount)
{
  int foods[FOODS];
  for(int i=0;i<FOODS;i++)
  {
    items[i] = i;
  }

  shuffle(foods,FOODS);

  for(int j=0;i<playerCount+1,i++)
  {
    innFoods[j] = foods[j];
  }
}

void init_shop(int* shopItems)
{
  int items[ITEMS];
  for(int i=0;i<ITEMS;i++)
  {
    items[i] = i;
  }

  shuffle(items,ITEMS);

  for(int j=0;i<3,i++)
  {
    shopItems[j] = items[j];
  }
}

int init_hotspring()
{
  return 2+rand()%2;
}

int init_encounter(Player* player)
{
  int type ;
  int choices[ENCOUNTERS];
  int choiceNb = 4;
  choices[0] = 0;
  choices[1] = 4;
  choices[2] = 5;
  choices[3] = 6;
  for (int i = choiceNb; i < ENCOUNTERS; i++)
  {
    // if (!pano_complete)
		if (1)
    {
      choices[choiceNb] = i;
      choiceNb++;
    }
  }
  shuffle(choices, choiceNb);

  return choices[0];
}
