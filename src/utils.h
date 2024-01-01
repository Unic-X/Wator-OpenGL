#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

#ifndef UTILS_H_
#define UTILS_H_
typedef struct PlanerCoordinates{
  int x;
  int y;
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


typedef enum Direction{
  East,
  West,
  South,
  North
} direction;


typedef struct Vector{
  size_t size;
  Creature *data;
  size_t capacity;
} vector ;

vector * new_vec(size_t init_cap);

void free_vec(vector * v);

int vec_grow(vector * v,size_t capacity);

//Usage vec_add(vector,Creature)
Creature vec_add(vector * v, Creature data);

bool is_free(planer_c c,vector * fishes,vector * sharks);

#endif // !UTILS_H_
