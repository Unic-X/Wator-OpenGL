#include "shark.h"
#include "utils.h"
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>


bool moveShark(Creature *shark,vector * fishes,vector * sharks){
  
  shark->energy--; //Shark's Energy will always decrease
  printf("%d\n",shark->energy);
  if (shark->energy<=0) {
    for (size_t i = 0; i < sharks->size; i++) {
      if (sharks->data[i].energy <= 0) {
        vec_del(sharks, i);
      }
    }
 return false;

  } 

  planer_c * current_c = &(shark->coord);

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

  if (is_free_for_shark(east,fishes,sharks)) available[idx++] = east;
  if (is_free_for_shark(west,fishes,sharks)) available[idx++] = west;
  if (is_free_for_shark(north,fishes,sharks)) available[idx++] = north;
  if (is_free_for_shark(south,fishes,sharks)) available[idx++] = south;

  if (idx==0) {
    return true;
  }

  planer_c next = available[rand()%idx];
  
  for (size_t i = 0; i < fishes->size; i++) {
    if (fishes->data[i].coord.x == next.x &&
        fishes->data[i].coord.y == next.y 
    ) {
      shark->energy+=20;
      break;
    }
    
  }  

  if (shark->energy>=ENERGY_S && idx>0) { //Only Reproduce when no one nearby
    reproduceShark(shark,sharks,next);
    return true;
  }

  shark->coord = next;

}

planer_c reproduceShark(Creature * shark, vector * sharks,planer_c next_coordinate){

  #ifdef DEBUG_ON
    printf("REPRODUCING\n\n");
  #endif /* ifdef DEBUG_ON */
  Creature * daughter_shark= newShark(next_coordinate);
  shark->energy = ENERGY_S/2;
  daughter_shark->energy = ENERGY_S;
  vec_add(sharks, *daughter_shark);
  return daughter_shark->coord;
}


Creature * newShark(planer_c coords){
  Creature * c = malloc(sizeof(Creature));
  c->coord = coords;
  c->kin = Shark;
  c->energy = ENERGY_S; //Energy for fish => Reproducing energy some refer this as time instead
  return c;         
}


vector * gen_sharks(int number){
  vector * generated_sharks = new_vec(number);
  for (int i=0; i<number; i++) {
    int x = rand() % COLUMNS;
    int y = rand() % ROWS;
    planer_c c;
    c.x = x;c.y = y;
    Creature * new_shark = newShark(c);
    vec_add(generated_sharks, *new_shark);
  }
  return generated_sharks;

}

void drawShark(planer_c coords){
  glRectd(coords.x, coords.y, coords.x+1, coords.y+1);
}
