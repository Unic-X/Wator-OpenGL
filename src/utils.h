#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#ifndef UTILS_H_
#define UTILS_H_
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


typedef enum Direction{
  East,
  West,
  South,
  North
} direction;

bool is_free(planer_c){

}


#endif // !UTILS_H_
