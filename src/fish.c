#include "fish.h"
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>

/*
 *  Handles wrap around
 */


planer_c moveFish(Creature *fish,vector * fishes,vector * sharks){
  //Energy of fish never deplets but  only when they Reproduce
  
  fish->energy++; //Fish's Energy will always increase

  planer_c * current_c = &(fish->coord);

  planer_c east,west,north,south; //Neighbour cells

  east.x = current_c->x-1;
  east.y = current_c->y;
  wrapCoordinates(&east);

  west.x = current_c->x+1;
  west.y = current_c->y;
  wrapCoordinates(&west);

  south.x = current_c->x;
  south.y = current_c->y-1;
  wrapCoordinates(&south);
  
  north.x = current_c->x;
  north.y = current_c->y+1;
  wrapCoordinates(&north);

  //Check if any of the above coordinate is occupied

  planer_c available[4];

  size_t idx = 0;

  if (is_free(east,fishes,sharks)) available[idx++] = east;
  if (is_free(west,fishes,sharks)) available[idx++] = west;
  if (is_free(north,fishes,sharks)) available[idx++] = north;
  if (is_free(south,fishes,sharks)) available[idx++] = south;

  if (idx==0) {
    return fish->coord;
  }

  planer_c next = available[rand()%idx];
  if (fish->energy>=ENERGY_F && idx>0) { 
    reproduceFish(fish,fishes,next);
    return fish->coord;
  }

  fish->coord = next;

}

planer_c reproduceFish(Creature * fish, vector * fishes,planer_c next_coordinate){

  #ifdef DEBUG_ON
    printf("REPRODUCING\n\n");
  #endif /* ifdef DEBUG_ON */
  Creature * daughter_fish = new_fish(next_coordinate);
  fish->energy = 0;
  daughter_fish->energy = ENERGY_F/2;
  vec_add(fishes, *daughter_fish);
  return daughter_fish->coord;
}


Creature * new_fish(planer_c coords){
  Creature * c = malloc(sizeof(Creature));
  c->coord = coords;
  c->kin = Fish;
  c->energy = ENERGY_F; //Energy for fish => Reproducing energy some refer this as time instead
  return c;         
}


void drawFish(planer_c coords){
  glRectd(coords.x, coords.y, coords.x+1, coords.y+1);
}
