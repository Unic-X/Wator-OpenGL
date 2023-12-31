#include "fish.h"
#include "utils.h"
#include "gui.c"
#include <GL/gl.h>

planer_c moveFish(Creature *creature){
  //Energy of fish never deplets but  only when they Reproduce
  planer_c * current_c = &(creature->coord);

  planer_c east,west,north,south; //Neighbour cells

  east.x = current_c->x-1;
  east.y = current_c->y;


  west.x = current_c->x+1;
  west.y = current_c->y;


  south.x = current_c->x;
  south.y = current_c->y-1;

  
  north.x = current_c->x;
  north.y = current_c->y+1;



  //Check if any of the above coordinate is occupied if yes don't move each frame
  if (is_free(north)) {
  
  }

}
