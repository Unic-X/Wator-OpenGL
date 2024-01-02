#include "utils.c"
#include "gui.c"
#include <stdio.h>
#include <stdlib.h>

#define MIN_SIZE 2
#define DEBUG_ON

// 	The points on the torus are defined as

// x = x % width of the board => Each coordinate in X repeats after being > width of the board
// y = y % height of the board => Repeats after being > height of the board 



// TODO
// 0. Define a Vector                                   -- Done
// 1. Define for Generic Type                           -- Done(Defined for Creature Instead)
// 2. Represneting Toroidal Geometry in plane           -- Done
// 3. Simulating Prey/ Preadtor behaviour via rules    
// 4. Impl Quick Sort for the coordinates because : 
//    1. Takes nlogn for sorting
//    2. Sorting makes logn search easier (Binary Search)

//    nlogn calls and more logn search?
//
//
//
// Rules for fish
// P1. Prey fish move randomly to free neighboring cells
// P2. Once the breed time is up a new fish spawns in a free neighboring cell 
// and the parents breed time is reset.
//
//
// Rules for Sharks(Preadtor)
// P1. Sharks move randomly to neighboring cells that are free or occupied by (non shark) fish.
// P2. If the cell to which the shark is moving is occupied by other fish it is consumed. The energy of the shark increases by a predefined value.
// P3. If the shark has enough energy it spawns offspring in a free neighboring cell.
// P4. Sharks lose a small fixed ammount of energy with every time step.
// P5. A shark dies if its energy level drops to zero.


int main(int argc, char** argv )
{ 
  main_loop(argc,argv);
}






