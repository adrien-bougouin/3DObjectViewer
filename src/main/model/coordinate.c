/*!
 * \file    coordinate.c
 *
 * \author  Adrien Bougouin <adrien.bougouin@gmail.com>
 */

#include <stdlib.h>
#include <string.h>

#include "coordinate.h"
#include "../util/string_iterator.h"

//==============================================================================
// Private functions
//==============================================================================

unsigned short coordinate_value(string_iterator_t *it, float *value) {
  unsigned short done = 0;

  if(it->good) {
    *value = atof(it->current_string);

    done = 1;
  }

  return done;
}

//==============================================================================
// Public functions
//==============================================================================

coordinate_t *new_coordinate(const char *reffering_line) {
  coordinate_t      *self = NULL;
  string_iterator_t *it   = new_string_iterator(reffering_line,
                                                COORDINATE_DELIMITERS);
  unsigned short    do_x;
  float             x;
  unsigned short    do_y;
  float             y;
  unsigned short    do_z;
  float             z;
  unsigned short    do_h;
  float             h;

  do_x = coordinate_value(it, &x);
  next_string_iterator(it);
  do_y = coordinate_value(it, &y);
  next_string_iterator(it);
  do_z = coordinate_value(it, &z);
  next_string_iterator(it);
  do_h = coordinate_value(it, &h);

  if(do_x && do_y && do_z) {
    self = malloc(sizeof(coordinate_t));

    self->x = x;
    self->y = y;
    self->z = z;
  }

  if(self != NULL) {
    if(do_h) {
      self->h = h;
    }

    self->is_extended = do_h;
  }

  free_string_iterator(it);
  it = NULL;

  return self;
}

void free_coordinate(coordinate_t *self) {
  if(self != NULL) {
    free(self);
  }
}

