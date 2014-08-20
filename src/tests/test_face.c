#include <stdio.h>
#include <stdlib.h>

#include "../main/model/face.h"

void display_face(face_t *f) {
  if(f != NULL) {
    printf("f ");
    for(size_t i = 0; i < f->vertexes->nb_elements; ++i) {
      printf("%d", *((int *)item_of_vector(f->vertexes, i)));
      if(f->textures != NULL) {
        printf("/%d", *((int *)item_of_vector(f->textures, i)));
      }
      if(f->normals != NULL) {
        if(f->textures == NULL) {
          printf("/");
        }
        printf("/%d", *((int *)item_of_vector(f->normals, i)));
      }
      printf(" ");
    }
    printf("\n");
  } else {
    printf("Failed...\n");
  }
}

int main(int argc, char ** argv) {
  printf("Creation of faces\n\n");
  face_t *f1 = new_face("f 1 2 3");
  face_t *f2 = new_face("f 1/5 2/2 3/6 7/9");
  face_t *f3 = new_face("f 1//4 2//1 3//10 9//1 10//3");
  face_t *f4 = new_face("f 1/9/4 2/1/1 3/2/10 9/8/1");

  printf("Display the faces:\n\n");
  display_face(f1);
  display_face(f2);
  display_face(f3);
  display_face(f4);

  printf("\nDeletion of the faces\n");
  free_face(f1);
  f1 = NULL;
  free_face(f2);
  f2 = NULL;
  free_face(f3);
  f3 = NULL;
  free_face(f4);
  f4 = NULL;

  return 0;
}

