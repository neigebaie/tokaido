#include "square_action.h"

void inn(Player* player)
{
	printf("todo\n");
}

void shop(Player* player, int item)
{
	printf("todo\n");
}

void hotspring(Player* player, int hotSpringTk)
{
  player->bundleToken += hotSpringTk;
}

void temple(Player* player)
{
	printf("todo\n");
}

void farm(Player* player)
{
  player->coins +=3;
}

void encounter(Player* player, int choices)
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

void pano_mon(Player* player)
{
  player->panRice += 1;
}

void pano_ric(Player* player)
{
  player->panMount += 1;
}

void pano_sea(Player* player)
{
  player->panSea += 1;
}
