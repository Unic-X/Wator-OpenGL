#include "utils.h"

#ifndef SHARK_H_   
#define SHARK_H_
#define BREEDING_T_S 12

int ENERGY_S = 4;

void moveShark(Creature *** sea, int alt, int i, int j);

void drawShark(planer_c coords);

planer_c reproduceShark(Creature * creature,vector * sharks,planer_c next_coordinate);

Creature * newShark(planer_c coords);

#endif // FISH_H_
