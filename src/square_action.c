#include "square_action.h"

//srand(time(NULL));

void inn (Player* player)
{

}

void shop ()
{

}

void hotspring (Player* player,int hotToken)
{
  player->bundleToken += hotToken ;
}

void temple (Player* player)
{

}

void farm (Player* player)
{
  player->coins +=3 ;
}

void encounter (int choices)
{
    switch (choices)
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
        player->templeCoins +=3 ;
      break ;

      case 5 :
        player->coins +=3 ;
      break ;

      case 6 :
        player->bundleToken +=3 ;
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
