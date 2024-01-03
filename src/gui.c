#include <GL/freeglut_std.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <time.h>
#include "fish.c"
#include "shark.c"

#ifndef GUI_H_
#define GUI_H_

unsigned long FPS = 30;

vector * fishes;
vector * sharks;


void square(int x,int y,char R,char G,char B){
  glLineWidth(0.1);
  glColor3ub(R,G,B);
  glBegin(GL_LINE_LOOP);
    glVertex2f(x,y);
    glVertex2f(x+1,y);
    glVertex2f(x+1,y+1);
    glVertex2f(x,y+1);
  glEnd();
}


void drawGrid(){
  for (int x=0; x<COLUMNS; x++) {
    for (int y = 0; y < ROWS; y++) {
      square(x,y,(char)255,(char)255,(char)255);
    }
  }
}

void draw_border(int x,int y){
  glColor3ub(255.0 ,255.0 , 255.0);
  glBegin(GL_LINE_LOOP);
    glVertex2d(x, y);
    glVertex2d(x+1, y);
    glVertex2d(x+1, y+1);
    glVertex2d(x, y+1);
  glEnd(); 



}

void display() {  // Display function will draw the image. baiscally the main drawing loop
    
    #ifndef DEBUG_ON
    
      printf("CURRENT FISHES %lu\n",fishes->size);
      printf("CURRENT SHARK %lu\n",sharks->size);
  
    #endif /* ifndef DEBUG_ON */

    glClearColor( 0.3, 0.2, 0.3, 1 );  // (In fact, this is the default.)
    glClear( GL_COLOR_BUFFER_BIT );
    drawGrid();

    //Draw Fish
    for (size_t i = 0; i < fishes->size; i++) {
      glColor3ub(121,183,205);
      moveFish(&(fishes->data[i]), fishes, sharks);
      drawFish(fishes->data[i].coord);
      float x = fishes->data[i].coord.x;
      float y = fishes->data[i].coord.y;
      draw_border(x, y); 
    }

    //Draw Shark
    for (size_t i = 0; i < sharks->size; ++i) {
      glColor3ub(255,139,97);
      if(!moveShark(&(sharks->data[i]), fishes, sharks)){
        --i;
      };
      drawShark(sharks->data[i].coord);
      float x = sharks->data[i].coord.x;
      float y = sharks->data[i].coord.y;
      draw_border(x, y);
    }
    
    glutSwapBuffers(); 
 
}

void reshape_callback(int width,int height){
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, COLUMNS, 0.0, COLUMNS, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
}

void timer_func(){ //For setting up FPS
  glutPostRedisplay();
  glutTimerFunc(1000/FPS,timer_func,0);
}

void keyboard_callback(int key,int _,int __){
  switch (key) {
    case GLUT_KEY_UP:
      FPS++;
      break;
    case GLUT_KEY_DOWN:
      if (FPS==1) break;
        FPS--;
      break;
  }
}

void set_spawn_rate(unsigned char key,int _,int __){
  switch (key) {
    case 'a':
      if (ENERGY_F==0) break;
        ENERGY_F--;
    case 'd':
      ENERGY_F++;
    case 'w':
      ENERGY_S++;
    case 's':
      if (ENERGY_S==0) break;
        ENERGY_S--;
    
  }
}

int main_loop( int argc, char** argv) {  // Initialize GLUT and 
    srand(time(0));
    sharks = gen_sharks(100);
    fishes = gen_fish(3000);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);    
    glutInitWindowSize(900,900);         // Size of display area, in pixels.
    glutCreateWindow("WatorGL"); // Parameter is window title.
    glutDisplayFunc(display); // Called when the window needs to be redrawn.
    glutReshapeFunc(reshape_callback); // In order to preserve the grid
    glutTimerFunc(0, timer_func,0);
    glutSpecialFunc(keyboard_callback);
    glutKeyboardFunc(set_spawn_rate);
    glutMainLoop(); // Run the event loop!  This function does not return.
    return 0;
}


#endif /* ifndef GUI_H_ */
