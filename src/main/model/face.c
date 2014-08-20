/*!
 * \file    face.c
 *
 * \author  Adrien Bougouin <adrien.bougouin@gmail.com>
 */

#include <stdlib.h>
#include <string.h>

#include "face.h"
#include "../util/string_iterator.h"

//==============================================================================
// Private functions
//==============================================================================

unsigned int nb_delimiters(const char *line, const char *delimiters) {
  unsigned int result = 0;

  for(size_t i = 0; i < strlen(line); ++i) {
    size_t          j     = 0;
    unsigned short  found  = 0;

    while(j < strlen(delimiters) && !found) {
      if(line[i] == delimiters[j]) {
        ++result;

        found = 1;
      }

      ++j;
    }
  }

  return result;
}

void add_point(face_t *self, const char *point_string) {
  string_iterator_t *it;
  int               *v;
  int               *vt;
  int               *vn;

  switch(nb_delimiters(point_string, SUB_DELIMITER)) {
    // f v1 v2 v3 [v*]*
    case 0:
      v = malloc(sizeof(int));

      *v = atoi(point_string);
      add_to_vector(self->vertexes, v);
    break;

    // f v1/vt1 v2/vt2 v3/vt3 [v*/vt*]*
    case 1:
      it = new_string_iterator(point_string, SUB_DELIMITER);
      v  = malloc(sizeof(int));
      vt = malloc(sizeof(int));

      if(self->textures == NULL) {
        self->textures = new_vector(MINIMAL_POINTS);
      }

      *v = atoi(it->current_string);
      add_to_vector(self->vertexes, v);
      
      next_string_iterator(it);

      *vt = atoi(it->current_string);
      add_to_vector(self->textures, vt);

      free_string_iterator(it);
    break;

    // f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3 [v*/vt*/vn*]*
    case 2:
      it = new_string_iterator(point_string, SUB_DELIMITER);
      v  = malloc(sizeof(int));
      vt = malloc(sizeof(int));
      vn = malloc(sizeof(int));

      if(self->textures == NULL) {
        self->textures = new_vector(MINIMAL_POINTS);
      }
      if(self->normals == NULL) {
        self->normals = new_vector(MINIMAL_POINTS);
      }

      *v = atoi(it->current_string);
      add_to_vector(self->vertexes, v);

      next_string_iterator(it);

      *vn = atoi(it->current_string);

      next_string_iterator(it);

      // case ?/?/?
      if(it->good) {
        *vt = *vn;
        add_to_vector(self->textures, vt);

        *vn = atoi(it->current_string);
      // case ?//?
      } else {
        free(vt);
        free_vector(self->textures);
        self->textures = NULL;
      }

      add_to_vector(self->normals, vn);

      free_string_iterator(it);
    break;
  }
}

//==============================================================================
// Public functions
//==============================================================================

face_t *new_face(const char *reffering_line) {
  face_t *self = NULL;

  // WARNING: implies that there is no useless spaces
  if(nb_delimiters(reffering_line, MAIN_DELIMITERS) > MINIMAL_POINTS) {
    string_iterator_t *it = new_string_iterator(reffering_line,
                                                MAIN_DELIMITERS);

    self = malloc(sizeof(face_t));
    self->vertexes  = new_vector(MINIMAL_POINTS);
    self->textures = NULL;
    self->normals = NULL;

    while(it->good) {
      add_point(self, it->current_string);

      next_string_iterator(it);
    }

    free_string_iterator(it);
  }

  return self;
}

void free_face(face_t *self) {
  if(self != NULL) {
    free_vector(self->vertexes);
    free_vector(self->textures);
    free_vector(self->normals);
    free(self);
  }
}

