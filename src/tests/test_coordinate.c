#include <stdio.h>
#include <stdlib.h>

#include "../main/model/coordinate.h"

void display_coordinate(coordinate_t *c) {
  printf("  c = (%.1f, %.1f, %.1f", c->x, c->y, c->z);
  if(c->is_extended) {
    printf(", %.1f)\n", c->h);
  } else {
    printf(")\n");
  }
}

int main(int argc, char ** argv) {
  printf("Creation of coordinates\n\n");
  coordinate_t *c1 = new_coordinate("v 1.0 0.0 2.0");
  coordinate_t *c2 = new_coordinate("v 0.0 0.5 3.0 1.0");

  printf("Display the coordinates:\n\n");
  display_coordinate(c1);
  display_coordinate(c2);

  printf("\nDeletion of the coordinates\n");
  free_coordinate(c1);
  c1 = NULL;
  free_coordinate(c2);
  c2 = NULL;

  return 0;
}

