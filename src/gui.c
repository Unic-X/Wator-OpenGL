#include <GL/freeglut_std.h>
#include <bits/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <pthread.h>
#include "fish.c"
#include "shark.c"

#ifndef GUI_H_
#define GUI_H_

unsigned long FPS = 30;

vector * fishes;
vector * sharks;

uint32_t gettickcount()
{
  struct timespec ts;

  clock_gettime(CLOCK_MONOTONIC_COARSE, &ts);
  return (1000 * ts.tv_sec + ts.tv_nsec / 1000000);
}

void fps()
{    
    static float framesPerSecond    = 0.0f;       // This will store our fps
    static float lastTime   = 0.0f;       // This will hold the time from the last frame
    float currentTime = gettickcount() * 0.001f;    
    ++framesPerSecond;
    if( currentTime - lastTime > 1.0f )
    {
        lastTime = currentTime;
        fprintf(stderr, "FPS:%d\n", (int)framesPerSecond);
        framesPerSecond = 0;
    }
}


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

static inline void drawFishes(){
 for (size_t i = 0; i < fishes->size; i++) {
      glColor3ub(121,183,205);
      drawFish(fishes->data[i].coord);
      float x = fishes->data[i].coord.x;
      float y = fishes->data[i].coord.y;
      draw_border(x, y); 
    }
}

void* moveFishesThread() {
    for (size_t i = 0; i < fishes->size; i++) {
        moveFish(&(fishes->data[i]), fishes, sharks);
    }
    return NULL;
}

void* moveSharksThread() {
    for (size_t i = 0; i < sharks->size; i++) {
      if(!moveShark(&(sharks->data[i]), fishes, sharks)){
        --i;
      };
    }
    return NULL;
}

static inline void drawSharks(){

 for (size_t i = 0; i < sharks->size; ++i) {
      glColor3ub(255,139,97);
     
      drawShark(sharks->data[i].coord);
      float x = sharks->data[i].coord.x;
      float y = sharks->data[i].coord.y;
      draw_border(x, y);
    }
}

void display() {  // Display function will draw the image. baiscally the main drawing loop
    
    #ifdef DEBUG_ON
    
      printf("CURRENT FISHES %lu\n",fishes->size);
      printf("CURRENT SHARK %lu\n",sharks->size);
  
    #endif /* ifndef DEBUG_ON */
    
    pthread_t fishes_t,sharks_t;
  
    glClearColor( 0.3, 0.2, 0.3, 1 );  // (In fact, this is the default.)
    glClear( GL_COLOR_BUFFER_BIT );
    drawGrid();
    //Draw Fish
    
    pthread_create(&fishes_t, NULL, moveFishesThread, NULL);
    pthread_create(&sharks_t, NULL, moveSharksThread, NULL);

    
    pthread_join(fishes_t, NULL);
    pthread_join(sharks_t, NULL);

    drawFishes();
    //Draw Shark
   
    drawSharks();

    glutSwapBuffers(); 
    fps();
 
}

void reshape_callback(int width,int height){
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, ROWS, COLUMNS, 0.0, -1.0, 1.0);
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
    case 'a' | 'A':
      if (ENERGY_F==0) break;
        ENERGY_F--;
        break;
    case 'd' | 'D':
      ENERGY_F++;
      break;
    case 'w' | 'W':
      ENERGY_S++;
      break;
    case 's' | 'S':
      if (ENERGY_S==0) break;
        ENERGY_S--;
        break;

  }
}

int main_loop( int argc, char** argv) {  // Initialize GLUT and 
   

    srand(time(NULL));   //Get random seed everytime" 
    sharks = gen_sharks(10);
    fishes = gen_fish(300);   
    
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
  
    free_vec(sharks);
    free_vec(fishes);
    return 0;
}


#endif /* if def !GUI_H_ */
