#ifndef SQUARE_INIT_H_
#define SQUARE_INIT_H_

#include <stdlib.h>

void init_inn(Food** foods); // initialise les repas du relai
void init_shop(Item** items); // initialise les souvenirs de l'échoppe
int init_encounter(Player* player); // choix aléatoire de rencontre
int init_hot_spring(); // nomre aléatoire de pts de victoires obtenus (entre 2 et 3)

#endif
