#include "utils.h"

#ifndef FISH_H_   
#define FISH_H_
#define ENERGY_F 20


planer_c moveFish(Creature * creature);

Creature drawFish(int x,int y);

planer_c reproduceFish(Creature * creature);

#endif // FISH_H_
