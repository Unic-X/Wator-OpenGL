#include "utils.h"

#ifndef SHARK_H_   
#define SHARK_H_
int ENERGY_S = 20;


bool moveShark(Creature * creature,vector * fishes,vector * sharks);

void drawShark(planer_c coords);

planer_c reproduceShark(Creature * creature,vector * sharks,planer_c next_coordinate);

Creature * newShark(planer_c coords);

#endif // FISH_H_
