#include "utils.h"

#ifndef FISH_H_   
#define FISH_H_
#define ENERGY_F 20


planer_c moveFish(Creature * creature,vector * fishes,vector * sharks);

Creature * drawFish(int x,int y);

planer_c reproduceFish(Creature * creature,vector * fishes,planer_c next_coordinate);

Creature * new_fish(planer_c coords);

#endif // FISH_H_
