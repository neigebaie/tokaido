#include <square_action.h>

SDL_bool buy_from_frame(Player* player, Frame* frame)
{
	SDL_bool bought = SDL_FALSE;
	if (frame->contentType == CONTENT_ITEM)
	{
		if (player->coins >= frame->content.item.price)
		{
			player->coins -= frame->content.item.price;
			player->bundleToken += tk_from_collection(frame->content.item, player->items, player->itemCount);
			player->items[player->itemCount] = frame->content.item;
			player->itemCount++;
			printf("ITEMCOUNT = %d\n", player->itemCount);
			bought = SDL_TRUE;
		}
	}
	else if (frame->contentType == CONTENT_FOOD)
	{
		if (player->coins >= frame->content.food.price)
		{
			player->coins -= frame->content.food.price;
			player->foods[player->foodCount] = frame->content.food;
			player->bundleToken += 6;
			player->foodCount++;
			printf("FOODCOUNT = %d\n", player->foodCount);
			bought = SDL_TRUE;
		}
	}
	printf("COINS = %d\n", player->coins);

	return bought;
}
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
  player->panRice += 1;
	player->bundleToken += player->panRice;
}

void action_pan_mount(Player* player)
{
  player->panMount += 1;
	player->bundleToken += player->panMount;
}

void action_pan_sea(Player* player)
{
  player->panSea += 1;
	player->bundleToken += player->panSea;
}
