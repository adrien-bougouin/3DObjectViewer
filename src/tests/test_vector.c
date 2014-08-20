#include <stdio.h>
#include <stdlib.h>

#include "../main/util/vector.h"

int main(int argc, char ** argv) {
  printf("Creation of a vector\n");
  vector_t *vector = new_vector(10);
  int *one = malloc(sizeof(int));
  int *two = malloc(sizeof(int));
  int *three = malloc(sizeof(int));
  int *four = malloc(sizeof(int));
  int *five = malloc(sizeof(int));
  int *six = malloc(sizeof(int));
  int *seven = malloc(sizeof(int));
  int *eight = malloc(sizeof(int));
  int *nine = malloc(sizeof(int));
  int *ten = malloc(sizeof(int));
  int *eleven = malloc(sizeof(int));

  printf("\nSize of the vector: %u\n", (unsigned int) vector->size);
  if(is_empty_vector(vector)) {
    printf("The vector is empty.\n");
  }
  printf("Number of elements in the vector: %u\n",
         (unsigned int) vector->nb_elements);

  printf("\nAdd 11 elements (1..11).\n");
  *one = 1;
  *two = 2;
  *three = 3;
  *four = 4;
  *five = 5;
  *six = 6;
  *seven = 7;
  *eight = 8;
  *nine = 9;
  *ten = 10;
  *eleven = 11;
  add_to_vector(vector, one);
  add_to_vector(vector, two);
  add_to_vector(vector, three);
  add_to_vector(vector, four);
  add_to_vector(vector, five);
  add_to_vector(vector, six);
  add_to_vector(vector, seven);
  add_to_vector(vector, eight);
  add_to_vector(vector, nine);
  add_to_vector(vector, ten);
  add_to_vector(vector, eleven);

  printf("\nSize of the vector: %u\n", (unsigned int) vector->size);
  if(!is_empty_vector(vector)) {
    printf("The vector isn't empty.\n");
  }
  printf("Number of elements in the vector: %u\n",
         (unsigned int) vector->nb_elements);

  printf("\nDisplay those elements:\n");
  printf("%d\n", *((int *) item_of_vector(vector, 0)));
  printf("%d\n", *((int *) item_of_vector(vector, 1)));
  printf("%d\n", *((int *) item_of_vector(vector, 2)));
  printf("%d\n", *((int *) item_of_vector(vector, 3)));
  printf("%d\n", *((int *) item_of_vector(vector, 4)));
  printf("%d\n", *((int *) item_of_vector(vector, 5)));
  printf("%d\n", *((int *) item_of_vector(vector, 6)));
  printf("%d\n", *((int *) item_of_vector(vector, 7)));
  printf("%d\n", *((int *) item_of_vector(vector, 8)));
  printf("%d\n", *((int *) item_of_vector(vector, 9)));
  printf("%d\n", *((int *) item_of_vector(vector, 10)));

  printf("\nDeletion of the vector\n");
  free_vector(vector);
  vector = NULL;

  return 0;
}

