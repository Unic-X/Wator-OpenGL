#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>   // freeglut.h might be a better alternative, if available.

#ifndef GUI_H_
#define GUI_H_

#define COLUMNS 100
#define ROWS 100
#define FPS 60

void square(int x,int y){
  glLineWidth(1.0);
  glColor3f(1.0,1.0,1.0);
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
      square(x,y);
    }
  }
}


void display() {  // Display function will draw the image. baiscally the main drawing loop
 
    glClearColor( 0.3, 0.2, 0.3, 1 );  // (In fact, this is the default.)
    glClear( GL_COLOR_BUFFER_BIT );
    drawGrid();
    glutSwapBuffers(); 
 
}

void reshape_callback(int width,int height){
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, COLUMNS, 0.0, COLUMNS, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
}

void timer_func(){
  glutPostRedisplay();
  glutTimerFunc(1000/FPS,timer_func,0);
}

int main( int argc, char** argv ) {  // Initialize GLUT and 

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);    
    glutInitWindowSize(1024,1024);         // Size of display area, in pixels.
    glutCreateWindow("WatorGL"); // Parameter is window title.
    glutDisplayFunc(display);            // Called when the window needs to be redrawn.
    glutReshapeFunc(reshape_callback); // In order to preserve the grid
    glutTimerFunc(0, timer_func,0);
    glutMainLoop(); // Run the event loop!  This function does not return.
    return 0;
}


#endif /* ifndef GUI_H_ */
