#include "utils.h"

#ifndef FISH_H_   
#define FISH_H_
#define BREEDING_T_F 2 

int ENERGY_F = 10;

planer_c moveFish(Creature * creature,vector * fishes,vector * sharks);

void drawFish(planer_c coords);

planer_c reproduceFish(Creature * creature,vector * fishes,planer_c next_coordinate);

Creature * new_fish(planer_c coords);

#endif // FISH_H_
