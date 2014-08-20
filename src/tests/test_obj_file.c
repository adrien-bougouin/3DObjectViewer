#include <stdlib.h>
#ifdef __MACH__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../main/model/obj_file.h"

obj_file_t *object;

void draw_axes() {
  glColor3f(1.0, 0.0, 0.0); // x = red
  glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(9.5, 0.0, 0.0);
  glEnd();
  glBegin(GL_TRIANGLES);
    glVertex3f(10.0, 0.0, 0.0);
    glVertex3f(9.5, 0.25, 0.0);
    glVertex3f(9.5, -0.25, 0.0);
  glEnd();

  glColor3f(0.0, 1.0, 0.0); // y = green
  glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 9.5, 0.0);
  glEnd();
  glBegin(GL_TRIANGLES);
    glVertex3f(0.0, 10.0, 0.0);
    glVertex3f(0.25, 9.5, 0.0);
    glVertex3f(-0.25, 9.5, 0.0);
  glEnd();

  glColor3f(0.0, 0.0, 1.0); // z = blue
  glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 9.5);
  glEnd();
  glBegin(GL_TRIANGLES);
    glVertex3f(0.0, 0.0, 10.0);
    glVertex3f(0.25, 0.0, 9.5);
    glVertex3f(-0.25, 0.0, 9.5);
  glEnd();

  glColor3f(1, 1, 1);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70, 640.0 / 480.0, 0.1, 100);
  gluLookAt(0,    18, 13, // look from
            0,    9,  6.5,  // look at
            0,    0,  1); // ViewUpVector
  /*
  // calibra
  gluLookAt(15,   15, 10, // look from
            -10,  0,  0,  // look at
            0,    0,  1); // ViewUpVector
  // bunny
  gluLookAt(0,    0.25, 0.25, // look from
            0,    0,    0,    // look at
            0,    0,    1);   // ViewUpVector
  // skyscraper
  gluLookAt(-50,  10, 55, // look from
            0,    0,  0,  // look at
            0,    0,  1); // ViewUpVector
  */

  draw_axes();
  display_obj_file(object);

  // changement de buffer pour l'affichage
  glutSwapBuffers();
}

int main(int argc, char **argv) {
  //object = new_obj_file("../sample/spaceship.obj");
  object = new_obj_file("../sample/dino.obj");
  //object = new_obj_file("../sample/cow.obj");
  //object = new_obj_file("../sample/skeleton.obj");
  //object = new_obj_file("../sample/car.obj");
  //object = new_obj_file("../sample/bunny.obj");
  //object = new_obj_file("../sample/duckyn.obj");
  //object = new_obj_file("../sample/skyscraper.obj");
  //object = new_obj_file("../sample/cessna.obj");
  //object = new_obj_file("../sample/lamp.obj");
  //object = new_obj_file("../sample/shuttle.obj");
  //object = new_obj_file("../sample/calibra.obj");

  // glut initialization
  glutInit(&argc, argv);
  // display parameters
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  // window parameters
  glutInitWindowPosition(200, 200);
  glutInitWindowSize(640, 480);
  glutCreateWindow("Sample test");

  // initialization
  glEnable(GL_DEPTH_TEST);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  //glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

  // display
  glutDisplayFunc(display);

  // waiting for events
  glutMainLoop();

  free_obj_file(object);
  object = NULL;
}

