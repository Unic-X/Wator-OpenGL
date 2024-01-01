#include "utils.h"

vector * new_vec(size_t init_cap){
  vector * v = (vector *)malloc(sizeof(vector));
  v->data = (Creature *)malloc(init_cap * sizeof(Creature));
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
  v->data = (Creature *)realloc(v->data, sizeof(Creature)*v->size*capacity);
  if (!v) return -1;
  return 0;  
};

Creature vec_add(vector * v, Creature data)
{
  if (v->size == v->capacity) {
    vec_grow(v, 2);
    v->capacity*=2;
  }
  return v->data[v->size++]=data;
}




bool is_free(planer_c c,vector * fishes,vector * sharks){
  for (int i=0; i<fishes->size ; i++) {
    planer_c coord = fishes->data[i].coord;
    if( c.x == coord.x && c.y == coord.y) return false;
  }

  for (int i=0; i<sharks->size ; i++) {
    planer_c coord = sharks->data[i].coord;
    if( c.x == coord.x && c.y == coord.y) return false;
  }

  return true;

}
