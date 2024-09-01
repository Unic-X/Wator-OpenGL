#include "shark.h"
#include "utils.h"
#include <GL/gl.h>

void moveShark(Creature ***sea, int old, int i, int j){

  sea[old][i][j].energy -= 1;
  sea[old][i][j].breeding_time += 1;

  int new = old^1;
  int dt[4][2];
  int fishEaten = false;

  dt[0][0] = (i+SIZE-1)%SIZE; dt[0][1] = j;
  dt[1][0] = (i+SIZE+1)%SIZE; dt[1][1] = j;
  dt[2][1] = (j+SIZE-1)%SIZE; dt[2][0] = i;
  dt[3][1] = (j+SIZE+1)%SIZE; dt[3][0] = i;


  int n = rand()%4;
  int newx, newy;
  for(int k = 0; k < 4; k++){

    int x = dt[n][0];
    int y = dt[n][1];
    if(sea[old][x][y].kin == Fish){
      sea[new][x][y].kin = Shark;
      sea[new][x][y].energy = sea[old][i][j].energy;
      sea[new][x][y].breeding_time = sea[old][i][j].breeding_time;
      sea[new][x][y].energy += 3;
      newx = x, newy = y;

      block(x,y);
      block(i,j);
      fishEaten = true;
      break;
    }
    n = (n+1)%4;
  }
  
  if(fishEaten == 0 && sea[old][i][j].energy <= 0){
    sea[new][i][j].kin = Water;
    block(i,j);
    return;
  }
  
  if(fishEaten == 1 && sea[old][i][j].breeding_time >= BREEDING_T_S &&
    sea[old][i][j].energy > 0){

    sea[new][i][j].kin = Shark;
    sea[new][i][j].breeding_time = 0;
    sea[new][newx][newy].breeding_time = 0;
    sea[new][i][j].energy = ENERGY_S;
    block(i,j);
  }

  if(fishEaten == true){
    return;
  }
  
  n = rand()%4;
  bool hasMoved = false;
  
  for(int k = 0; k < 4; k++){
    int x = dt[n][0];
    int y = dt[n][1];
    if(sea[old][x][y].kin == Water){
      sea[new][x][y].kin = Shark;
      copy(sea, x, y, i, j);
      block(x,y);
      block(i,j);
      
      hasMoved = true;
      newx = x;
      newy = y;
      break;
    }
    n = (n+1)%4;
  }

  if(hasMoved == true){
    if(sea[old][i][j].breeding_time > BREEDING_T_S){
      sea[new][newx][newy].breeding_time = 0;
    }
    return;
  }

  sea[new][i][j].kin = Shark;
  copy(sea, i, j, i, j);
}

void gen_sharks(Creature ***sea, unsigned long number){
  for (int i=0; i<number; i++) {
    int x = rand() % SIZE;
    int y = rand() % SIZE;
    if(sea[0][x][y].kin != Water){
      i--;
      continue;
    }

    sea[0][x][y].kin = Shark;
    sea[0][x][y].energy = ENERGY_S;
    sea[0][x][y].breeding_time = 0;
  }
}
