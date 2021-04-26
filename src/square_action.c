#include <square_action.h>

// buy_food(Food* food)
// {
//
// }

// auto-actions for bots ?

void action_inn(Player* player)
{
	printf("todo\n");
}

void action_shop(Player* player, int item)
{
	printf("todo\n");
}

void action_hot_spring(Player* player, int hotSpringTk)
{
  player->bundleToken += hotSpringTk;
}

void action_temple(Player* player)
{
	printf("todo\n");
}

void action_farm(Player* player)
{
  player->coins +=3;
}

void action_encounter(Player* player, int choices)
{
    switch (choices)
    {
      case 0 :
				printf("todo\n"); // Items a faire
      break;

      case 1 :
        player->panRice += 1;
      break;

      case 2 :
        player->panMount += 1;
      break;

      case 3 :
        player->panSea += 1;
      break;

      case 4 :
        player->templeCoins += 3;
      break;

      case 5 :
        player->coins +=3;
      break;

      case 6 :
        player->bundleToken +=3;
      break;
    }
}

void action_pan_rice(Player* player)
{
  player->panMount += 1;
}

void action_pan_mount(Player* player)
{
  player->panRice += 1;
}

void action_pan_sea(Player* player)
{
  player->panSea += 1;
}
