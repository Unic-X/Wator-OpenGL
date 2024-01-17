#include "utils.h"

#ifndef _FISH_H_   
#define _FISH_H_
#define BREEDING_T_F 1

int ENERGY_F = 10;

void moveFish(Creature * creature,vector * fishes,vector * sharks);

void drawFish(planer_c coords);

planer_c reproduceFish(Creature * creature,vector * fishes,planer_c next_coordinate);

Creature * new_fish(planer_c coords);

vector * gen_fish(int number);

#endif // ! defined _FISH_H_
