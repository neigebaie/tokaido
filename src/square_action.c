#include "square_action.h"

// srand(time(NULL));

void inn (Player* player)
{

}

void shop (Player* player)
{

}

void hotspring (Player* player)
{

}

void temple (Player* player)
{

}

void farm (Player* player)
{
  player->coins +=3 ;
}

void encounter (Player* player)
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
    switch (choices[0])
    {
      case 0 :                                    //Items a faire

      break ;

      case 1 :
        player->panRice += 1;
      break ;

      case 2 :
        player->panMount += 1;
      break ;

      case 3 :
        player->panSea += 1;
      break ;

      case 4 :
        player->templeCoins += 3;
      break ;

      case 5 :
        player->coins +=3;
      break ;

      case 6 :
        player->bundleToken +=3;
      break ;
    }
}

void pano_mon (Player* player)
{
  player->panRice += 1;
}

void pano_ric (Player* player)
{
  player->panMount += 1;
}

void pano_sea (Player* player)
{
  player->panSea += 1;
}
