/*!
 * \file    vector.c
 *
 * \author  Adrien Bougouin <adrien.bougouin@gmail.com>
 */

#include <stdlib.h>

#include "vector.h"

//==============================================================================
// Private Functions
//==============================================================================

void double_size(vector_t *self) {
  size_t new_size = self->size * 2;
  void **new_elements = calloc(new_size, sizeof(void *));

  for(size_t i = 0; i < new_size; ++i) {
    if(i < self->size) {
      new_elements[i] = self->elements[i];
    } else {
      new_elements[i] = NULL;
    }
  }

  self->elements  = new_elements;
  self->size      = new_size;
}

//==============================================================================
// Public Functions
//==============================================================================

vector_t *new_vector(size_t initial_size) {
  vector_t *self = malloc(sizeof(vector_t));

  if(initial_size != 0) {
    self->size = initial_size;
  } else {
    self->size = 1;
  }

  self->elements    = calloc(self->size, sizeof(void *));
  self->nb_elements = 0;

  for(size_t i = 0; i < self->size; ++i) {
    self->elements[i] = NULL;
  }

  return self;
}

void free_vector(vector_t *self) {
  if(self != NULL) {
    for(size_t i; i < self->nb_elements; ++i) {
      free(self->elements[i]);
    }
    free(self->elements);
    free(self);
  }
}

int is_empty_vector(vector_t *self) {
  return (self == NULL || self->nb_elements == 0);
}

void add_to_vector(vector_t *self, void *element) {
  if(self != NULL) {
    self->elements[self->nb_elements] = element;
    ++self->nb_elements;

    if(self->nb_elements == self->size) {
      double_size(self);
    }
  }
}

void *item_of_vector(vector_t *self, size_t index) {
  if(self == NULL || index >= self->size) {
    return NULL;
  } else {
    return self->elements[index];
  }
}

