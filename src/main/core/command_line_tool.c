/*!
 * \file    command_line_tool.c
 *
 * \author  Adrien Bougouin <adrien.bougouin@gmail.com>
 */

#ifdef __MACH__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <string.h>
#include <math.h>
#ifdef _WIN32
#include <windows.h>
#endif

#include "command_line_tool.h"
#include "../model/obj_file.h"

void display() {
  lazy_obj_file_t *object           = item_of_vector(objects, current_object);
  float           cam_x             = sin(theta / 180.0 * PI) * distance;
  float           cam_y             = sin(phi   / 180.0 * PI) * distance;
  float           cam_z             = cos(theta / 180.0 * PI) * distance;
  GLfloat         light_position[4] = {cam_x, cam_y, cam_z, 1.0};

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glutSetWindowTitle(object->filename);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  if(smooth_wanted) {
    glShadeModel(GL_SMOOTH);
  } else {
    glShadeModel(GL_FLAT);
  }

  gluPerspective(70.0, window_width / window_height, 0.1, 100);
  gluLookAt(cam_x,    cam_y,    cam_z,
            center_x, center_y, center_z,
            0.0,      1.0,      0.0);

  draw_axis();
  draw_floor();
  // FIXME calculate the normal of the faces which haven't
  glNormal3f(cam_x, 1.0, cam_z);
  display_obj_file(get_obj_file_instance(object));

  glutSwapBuffers();
}

void reshape(int width, int height) {
  if(height == 0) {
    height = 1;
  } 

  glViewport(0, 0, width, height);
  window_width  = width;
  window_height = height;
}

void process_keyboard(unsigned char key, int x, int y) {
  switch(key) {
    case '1':
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

      glutPostRedisplay();
    break;

    case '2':
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

      glutPostRedisplay();
    break;

    case '3':
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

      glutPostRedisplay();
    break;

    case '4':
      smooth_wanted = !smooth_wanted;

      glutPostRedisplay();
    break;

    case '5':
      axis_wanted = !axis_wanted;

      glutPostRedisplay();
    break;

    case '+':
      if(distance > 1) {
        --distance;
      }

      glutPostRedisplay();
    break;

    case '-':
      ++distance;
      if(distance < 0) {
        --distance;
      }

      glutPostRedisplay();
    break;

    case 'z':
      ++center_y;

      glutPostRedisplay();
    break;

    case 's':
      --center_y;

      glutPostRedisplay();
    break;

    case 'q':
      if(current_object > 0) {
        --current_object;
      } else {
        current_object = objects->nb_elements - 1;
      }

      glutPostRedisplay();
    break;

    case 'd':
      if(current_object < (objects->nb_elements - 1)) {
        ++current_object;
      } else {
        current_object = 0;
      }

      glutPostRedisplay();
    break;

    case 'e':
      delete_objects();
      exit(0);
    break;
  }
}

void process_mouse(int button, int state, int x, int y) {
  switch(button) {
    case GLUT_LEFT_BUTTON:
      if(state == GLUT_DOWN) {
        mouse_x                   = x;
        mouse_y                   = y;
        mouse_left_button_pressed = 1;
      } else {
        mouse_left_button_pressed = 0;
      }
    break;

    default:
    break;
  }
}

void process_mouse_motion(int x, int y) {
  if(mouse_left_button_pressed) {
    if(x < mouse_x) {
      turn_left();
    } else if(x > mouse_x) {
      turn_right();
    }
    if(y < mouse_y) {
      down();
    } else if(y > mouse_y) {
      up();
    }

    mouse_x = x;
    mouse_y = y;

    glutPostRedisplay();
  }
}

void up() {
  if(phi <= 90 - STEP) {
    phi += STEP;
  }
}

void down() {
  if(phi >= -90 + STEP) {
    phi -= STEP;
  }
}

void turn_left() {
  theta += STEP;
}

void turn_right() {
  theta -= STEP;
}

void load_objects(char **argv) {
  char **it = argv;

  objects = new_vector(2);

  ++it;
  while(*it) {
    add_to_vector(objects, new_lazy_obj_file(*it));

    ++it;
  }
}

void delete_objects() {
  for(size_t i = 0; i < objects->nb_elements; ++i) {
    free_lazy_obj_file(item_of_vector(objects, i));
  }
  free(objects);
  objects = NULL;
}

void init() {
  objects                   = NULL;
  current_object            = 0;
  center_x                  = 0.0;
  center_y                  = 0.0;
  center_z                  = 0.0;
  theta                     = 45.0;
  phi                       = 45.0;
  distance                  = 15.0;
  window_width              = 800.0;
  window_height             = 600.0;
  axis_wanted               = 1;
  smooth_wanted             = 0;
  mouse_x                   = 0;
  mouse_y                   = 0;
  mouse_left_button_pressed = 0;
}

void draw_axis() {
  if(axis_wanted) {
    glDisable(GL_LIGHTING);

    glColor3f(1.0, 0.0, 0.0);
    glRasterPos3f(10.2, 0.0, 0.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'x');
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(10.0, 0.0, 0.0);
    glEnd();

    glColor3f(0.0, 1.0, 0.0);
    glRasterPos3f(0.0, 10.2, 0.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'y');
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 10.0, 0.0);
    glEnd();

    glColor3f(0.0, 0.0, 1.0);
    glRasterPos3f(0.0, 0.0, 10.2);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'z');
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 10.0);
    glEnd();

    glEnable(GL_LIGHTING);
    glColor3f(1, 1, 1);
  }
}

void draw_floor() {
  if(axis_wanted) {
    glDisable(GL_LIGHTING);


    for(float x = 30.0; x >= -30.0; x -= 3) {
      glColor3f(1.0, 1.0, 1.0);
      glBegin(GL_LINES);
      glVertex3f(x, center_y, 30.0);
      glVertex3f(x, center_y, -30.0);
      glEnd();
    }
    for(float z = 30.0; z >= -30.0; z -= 3) {
      glColor3f(1.0, 1.0, 1.0);
      glBegin(GL_LINES);
      glVertex3f(30.0, center_y, z);
      glVertex3f(-30.0, center_y, z);
      glEnd();
    }

    glEnable(GL_LIGHTING);
    glColor3f(1, 1, 1);
  }
}

void print_help() {
  char *help = calloc(1024, sizeof(char));

  strcpy(help, "Welcome to this simple 3D Object Viewer\n\n");
  strcat(help, "The following commands are used to manage the view of your object:\n");
  strcat(help, "  1: The polygons are filled\n");
  strcat(help, "  2: The polygons are drawn as line segments\n");
  strcat(help, "  3: The polygons are drawn by their edges\n");
  strcat(help, "  4: Enable/Disable the smooth\n");
  strcat(help, "  5: Enable/Disable the axis and the floor\n");
  strcat(help, "  z: Set up the floor\n");
  strcat(help, "  s: Set down the floor\n");
  strcat(help, "  d: Next object\n");
  strcat(help, "  q: Previous object\n");
  strcat(help, "  e: Exit\n");
  strcat(help, "The mouse is available too\n\n");
  strcat(help, "Enjoy ;)\n");

#ifdef _WIN32
  MessageBox(0, help, "Usage", MB_OK );
#else
  printf("%s", help);
#endif

  free(help);
}

int main(int argc, char **argv) {
  if(argc >= 2) {
    init();
    print_help();
    load_objects(argv);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("3D Object Viewer in OpenGL");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutKeyboardFunc(process_keyboard);
    glutMouseFunc(process_mouse);
    glutMotionFunc(process_mouse_motion);

    display();
    glutMainLoop();
  } else {
#ifdef _WIN32
    char *help = calloc(128, sizeof(char));

    strcpy(help, "Launch the software with arguments.\n");
    strcat(help, "Each argument is a .obj file path.");

    MessageBox(0, help, "This is a command line tool...", MB_OK);
#else
    printf("Usage: %s [filename]*\n", argv[0]);
#endif
  }

  return 0;
}

