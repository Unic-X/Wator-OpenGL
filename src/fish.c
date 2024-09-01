#include "fish.h"
#include "shark.h"
#include <GL/gl.h>
#include <stdlib.h>

void moveFish(Creature ***sea, int old, int i, int j){

  sea[old][i][j].breeding_time += 1;

  int new = old^1;
  int dt[4][2];
  int sharkx, sharky;

  dt[0][0] = (i+SIZE-1)%SIZE; dt[0][1] = j;
  dt[1][0] = (i+SIZE+1)%SIZE; dt[1][1] = j;
  dt[2][1] = (j+SIZE-1)%SIZE; dt[2][0] = i;
  dt[3][1] = (j+SIZE+1)%SIZE; dt[3][0] = i;
  
  int n = rand()%4;
  for(int k = 0; k < 4; k++){
    int x = dt[n][0];
    int y = dt[n][1];
    if(sea[old][x][y].kin == Shark){
      moveShark(sea, old, x, y);
      return;
    }
    n = (n+1)%4;
  }

  n = rand()%4;
  int hasMoved = false;
  int newx, newy;

  for(int k = 0; k < 4; k++){

    int x = dt[n][0]; int y = dt[n][1];
    if(sea[old][x][y].kin == Water){
      sea[new][x][y].kin = Fish;
      copy(sea, x, y, i, j);
      block(x,y);
      block(i,j);

      newx = x;
      newy = y;
      hasMoved = true;
      break;
    }
    n = (n+1)%4;
  }

  if(sea[old][i][j].breeding_time >= BREEDING_T_F && hasMoved == 1){
    sea[new][i][j].kin = Fish;
    sea[new][i][j].breeding_time = 0;
    sea[new][newx][newy].breeding_time = 0;
    block(i,j);
  }

  if(hasMoved == true){
    return;
  }

  sea[new][i][j].kin = Fish;
  copy(sea, i, j, i, j);
}

void gen_fish(Creature ***sea, int number){
  for (int i=0; i<number; i++) {
    int x = rand() % SIZE;
    int y = rand() % SIZE;
    if(sea[0][x][y].kin != Water){
      i--;
      continue;
    }

    sea[0][x][y].kin = Fish;
    sea[0][x][y].energy = 0;
    sea[0][x][y].breeding_time = 0;
  }
}
