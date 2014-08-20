/*!
 * \file    command_line_tool.h
 * \brief   A simple command line utility to watch the result of a .obj file.
 *
 * \author  Adrien Bougouin <adrien.bougouin@gmail.com>
 */

#ifndef __COMMAND_LINE_TOOL_H__
#define __COMMAND_LINE_TOOL_H__

#include <stdlib.h>

#include "../util/vector.h"

//==============================================================================
// Constants
//==============================================================================

#define PI    3.14159265358979323846
#define STEP  2.5

//==============================================================================
// Global variables
//==============================================================================

vector_t        *objects;
size_t          current_object;
float           center_x;
float           center_y;
float           center_z;
float           theta;
float           phi;
float           distance;
float           window_width;
float           window_height;
unsigned short  axis_wanted;
unsigned short  smooth_wanted;
int             mouse_x;
int             mouse_y;
unsigned short  mouse_left_button_pressed;

//==============================================================================
// Function prototypes
//==============================================================================

void display();
void reshape(int width, int height);
void process_keyboard(unsigned char key, int x, int y);
void process_mouse(int button, int state, int x, int y);
void process_mouse_motion(int x, int y);
void up();
void down();
void turn_left();
void turn_right();
void load_objects(char **argv);
void delete_objects();
void init();
void draw_axis();
void draw_floor();
void print_help();

#endif // __COMMAND_LINE_TOOL_H__

