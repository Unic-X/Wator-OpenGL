#include "utils.h"

int ENERGY_S = 4;


#ifndef SHARK_H_   
#define SHARK_H_
#define BREEDING_T_S 12


bool moveShark(Creature * creature,vector * fishes,vector * sharks);

void drawShark(planer_c coords);

planer_c reproduceShark(Creature * creature,vector * sharks,planer_c next_coordinate);

Creature * newShark(planer_c coords);

vector * gen_sharks(int number);

#endif // FISH_H_
