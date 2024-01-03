#include "shark.h"
#include "utils.h"
#include <GL/gl.h>
#include <stdio.h>
#include <time.h>

bool moveShark(Creature *shark,vector * fishes,vector * sharks){
  
 //Shark's Energy will always decrease
  shark->breeding_time++;

  if (shark->energy==0) {
    for (size_t i = 0; i < sharks->size; ++i) {
      unsigned long t = sharks->size;
      if (sharks->data[i].energy == 0 &&
          sharks->data[i].coord.x == shark->coord.x &&
          sharks->data[i].coord.y == shark->coord.y 
      ) {
        vec_del(sharks, i);

      }
    }
    return false; //Cannot move starved shark
  } 

  //Will exist and will have less energy
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

  if (is_free_for_shark(east,sharks)) available[idx++] = east;
  if (is_free_for_shark(west,sharks)) available[idx++] = west;
  if (is_free_for_shark(north,sharks)) available[idx++] = north;
  if (is_free_for_shark(south,sharks)) available[idx++] = south;

  if (idx==0) {
    return true; //Don't Move 
  }
  
  shark->energy--;

  planer_c next = available[rand()%idx]; //Random Movements of shark only

  bool found = false;  
  

  //Check if nearby any fish if yes move there else don't
  // for (size_t i =0; i<idx; i++) { 
  //   for (size_t j = 0; j < fishes->size; j++) {
  //     if (fishes->data[j].coord.x == available[i].x &&
  //         fishes->data[j].coord.y == available[i].y
  //     ) {
  //       next = available[i];
  //       found = true;
  //     }
  //   }
  // }
  //  
  //Check if moved onto a fish and delete the fish from fishes vector
  for (size_t i = 0; i < fishes->size; i++) {
    if (fishes->data[i].coord.x == next.x &&
        fishes->data[i].coord.y == next.y 
    ) {
      shark->energy+=3;
      vec_del(fishes, i); 
      break;
    }
  }  

  //Reproduce when Energy >= 17 and when there are places to go to
  if (shark->breeding_time>=BREEDING_T_S && idx!=0) { //Only Reproduce when no one nearby
    reproduceShark(shark,sharks,next);
    return true;
  }

  shark->coord = next;
  return true;
  
}

planer_c reproduceShark(Creature * shark, vector * sharks,planer_c next_coordinate){

  #ifdef DEBUG_ON
    printf("REPRODUCING\n\n");
  #endif /* ifdef DEBUG_ON */
  
  Creature * daughter_shark= newShark(next_coordinate);
  shark->breeding_time = 0;
  vec_add(sharks, *daughter_shark);
  return daughter_shark->coord;
}


Creature * newShark(planer_c coords){
  Creature * c = malloc(sizeof(Creature));
  c->coord = coords;
  c->kin = Shark;
  c->breeding_time = 0;
  c->energy = ENERGY_S; //Energy for fish => Reproducing energy some refer this as time instead
  return c;         
}


vector * gen_sharks(unsigned long number){
  vector * generated_sharks = new_vec(256);
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
