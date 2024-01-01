#include "fish.h"
#include "utils.h"
#include "gui.c"

planer_c moveFish(Creature *creature){
  //Energy of fish never deplets but  only when they Reproduce
  planer_c * current_c = &(creature->coord);

  planer_c east,west,north,south; //Neighbour cells
  
  planer_c * empty = malloc(sizeof(planer_c)*4);

  east.x = current_c->x-1;
  east.y = current_c->y;


  west.x = current_c->x+1;
  west.y = current_c->y;


  south.x = current_c->x;
  south.y = current_c->y-1;

  
  north.x = current_c->x;
  north.y = current_c->y+1;


  //Check if any of the above coordinate is occupi

  free(empty);

}


Creature drawFish(int x,int y){
  Creature c;
  planer_c coords;
  coords.x = x, coords.y = y;
  c.coord = coords;
  c.kin = Fish;
  c.energy = ENERGY_F; //Energy for fish => Reproducing energy some refer this as time instead
  return c;         
}
