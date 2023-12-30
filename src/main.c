#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MIN_SIZE 2
#define DEBUG_ON

#define BOARD_SIZE 200

typedef struct Vector{
  size_t size;
  int  *data;
  size_t capacity;
} vector ;

typedef struct PlanerCoordinates{
  float_t x;
  float_t y;
} planer_c;

typedef enum kind{
  Fish,
  Shark
}kind;

typedef struct Creature{
  kind kin;
  planer_c coord;
  int energy;
} Creature;


Creature create_creature(kind k,int energy){
  Creature creature;
  planer_c coords;
  coords.x = rand() % BOARD_SIZE;
  
  switch (k) {
    case Fish:
      creature.kin = Fish;
      creature.energy = energy;
      creature.coord = coords;
      break;

    case Shark:
      creature.kin = Fish;
      creature.energy = energy;
      creature.coord = coords;
      break;
  }
  return creature;
}



// 	The points on the torus are defined as

// x = x % width of the board => Each coordinate in X repeats after being > width of the board
// y = y % height of the board => Repeats after being > height of the board 



// TODO
// 0. Define a Vector                                  -- Done
// 1. Define for Generic Type          
// 2. Represneting Toroidal Geometry in plane          -- Done
// 3. Simulating Prey/ Preadtor behaviour via rules    
//
//
// Rules for fish
// P1. Prey fish move randomly to free neighboring cells
// P2. Once the breed time is up a new fish spawns in a free neighboring cell and the parents breed time is reset.
//
//
// Rules for Sharks(Preadtor)
// P1. Sharks move randomly to neighboring cells that are free or occupied by (non shark) fish.
// P2. If the cell to which the shark is moving is occupied by other fish it is consumed. The energy of the shark increases by a predefined value.
// P3. If the shark has enough energy it spawns offspring in a free neighboring cell.
// P4. Sharks lose a small fixed ammount of energy with every time step.
// P5. A shark dies if its energy level drops to zero.



vector * new_vec(size_t init_cap){
  vector * v = malloc(sizeof(vector));
  v->data = malloc(init_cap * sizeof(typeof(v->data)));
  if (!(v->data)) fprintf(stderr, "Memory Error Cannot assign Vector ");
  v->size = 0;
  v->capacity = init_cap;
   #ifdef DEBUG_ON
    printf("Vector allocation at : %p \n",v);
  #endif //DEBUG_ON
  return v; //Success

}

void free_vec(vector * v){
  free(v->data);
  free(v);
}


int vec_grow(vector * v,size_t capacity){
  #ifdef DEBUG_ON
    printf("V_Resize: %lu to %lu \n",v->capacity,capacity);
  #endif //DEBUG_ON
  v->data = realloc(v->data, sizeof(typeof(v->data))*capacity);
  if (!v) return -1;
  return 0;  
};


int vec_add(vector * v, int data)
{
  if (v->size == v->capacity) {
    vec_grow(v, 2);
    v->capacity*=2;
  }
  return v->data[v->size++]=data;
}


int main()
{
  vector * v = new_vec(3);
  vec_add(v, 5);
  vec_add(v, 7);
  vec_add(v, 9);
  vec_add(v, 10);
  vec_add(v, 10);
  vec_add(v, 10);
  vec_add(v, 10);
  vec_add(v, 10);
}






