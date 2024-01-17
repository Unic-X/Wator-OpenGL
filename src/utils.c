#include "utils.h"
#include <string.h>
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
threadqueue * QUEUE;

pthread_mutex_t mutex;

vector * new_vec(size_t init_cap){
  vector * v = (vector *)malloc(sizeof(vector));
  v->data = (Creature *)malloc(init_cap * sizeof(Creature));
  if (!(v->data)) fprintf(stderr, "Memory Error Cannot assign Vector ");
  v->size = 0;
  v->capacity = init_cap;


  /***********DEBUGGING STUFF***********/
   #ifdef DEBUG_ON
    printf("V_ALLC: AT %p \n",v);
  #endif //DEBUG_ON
 /************************************/
  
  return v; //Success

}


NODE* get_node(int i,kind k){
    NODE * temp = (NODE *)malloc(sizeof(NODE));
    temp->k = k;
    temp->i = i;
    temp->link = NULL;
    return temp;
}

void enqueue(int i, kind k){

    NODE *temp = get_node(i,k);
    if(QUEUE->num_nodes == 0){
        QUEUE->head = temp;
        QUEUE->rear = temp;
    }else{
        QUEUE->rear->link = temp;
        QUEUE->rear = temp;
    }
    QUEUE->num_nodes++;
}

NODE* dequeue(){
    if(QUEUE->num_nodes == 0){
        return NULL;
    }
    else{
        NODE *temp = QUEUE->head;
        QUEUE->head = QUEUE->head->link;
        QUEUE->num_nodes--;

        if(QUEUE->num_nodes == 0){
            QUEUE->head = NULL;
            QUEUE->rear = NULL;
        }
        return temp;
    }
}


void vector_set(vector * v,int index, Creature c){
  if (index>=0 && index<v->size) v->data[index]=c; 
}


void free_vec(vector * v){
  free(v->data);
  free(v);
}

void vec_del(vector *v, int index) {
    
    errno = 0;
    if (index < 0 || index >= v->size)
    {
      fprintf(stderr, "INDEX > V.SIZE OR INDEX < 0 %s\n",strerror(errno));
    }
 
    for (int i = index - 1; i < v->size-1; i++)  
      {  
        v->data[i] = v->data[i+1]; // assign arr[i+1] to arr[i]  
      }  

    v->size--;
 
    if (v->size > 0 && v->size == v->capacity / 4)
      vec_grow(v, v->capacity/2);
}


int vec_grow(vector * v,size_t capacity){

  /***********DEBUGGING STUFF***********/
  #ifdef DEBUG_ON
    printf("V_RESIZE: %lu to %lu \n",v->capacity,capacity);
    printf("V_RESIZE: DATA FROM %p ",v->data);
  #endif //DEBUG_ON
  /************************************/

  v->data = (Creature *)realloc(v->data,sizeof(Creature)*capacity);

  #ifdef DEBUG_ON
  printf("MOVED TO %p\n",v->data);
  #endif //DEBUG_ON
  
  v->capacity = capacity;

  if (!v) return -1;
  return 0;  
};



void wrapCoordinates(planer_c *point) {
    // Wrap x-axis
    if (point->x < 0) {
        point->x = COLUMNS - 1;
    } else if (point->x >= COLUMNS) {
        point->x = 0;
    }

    // Wrap y-axis
    if (point->y < 0) {
        point->y = ROWS - 1;
    } else if (point->y >= ROWS) {
        point->y = 0;
    }
}


Creature vec_add(vector * v, Creature data)
{

  /***********DEBUGGING STUFF***********/
  #ifdef DEBUG_ON
    printf("V_ADD: AT %p, CAPACITY:%lu \n",v,v->capacity);
  #endif //DEBUG_ON
  /************************************/


  if (v->size == v->capacity) {
    vec_grow(v, v->capacity*2);
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


bool is_free_for_shark(planer_c c ,vector * sharks){

  for (int i=0; i<sharks->size ; i++) {
    planer_c coord = sharks->data[i].coord;
    if( c.x == coord.x && c.y == coord.y) return false;
  }

  return true;

}


int isCoordinateTaken(vector * creatures, int n, int x, int y){
    for (int i = 0; i < creatures->size; i++) {
        if (creatures->data[i].coord.x == x && creatures->data[i].coord.y == y) {
            return true; 
        }
    }
    return false; 
}
