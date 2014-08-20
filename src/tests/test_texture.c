#include <stdio.h>
#include <stdlib.h>

#include "../main/model/texture.h"

void display_texture(texture_t *t) {
  printf("  t = (%.1f, %.1f", t->u, t->v);
  if(t->is_extended) {
    printf(", %.1f)\n", t->w);
  } else {
    printf(")\n");
  }
}

int main(int argc, char ** argv) {
  printf("Creation of textures\n\n");
  texture_t *t1 = new_texture("v 1.0 2.0");
  texture_t *t2 = new_texture("v 0.0 3.0 1.0");

  printf("Display the textures:\n\n");
  display_texture(t1);
  display_texture(t2);

  printf("\nDeletion of the coordinates\n");
  free_texture(t1);
  t1 = NULL;
  free_texture(t2);
  t2 = NULL;

  return 0;
}

