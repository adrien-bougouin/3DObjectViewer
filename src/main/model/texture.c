/*!
 * \file    texture.c
 *
 * \author  Adrien Bougouin <adrien.bougouin@gmail.com>
 */

#include <stdlib.h>
#include <string.h>

#include "texture.h"
#include "../util/string_iterator.h"

//==============================================================================
// Private functions
//==============================================================================

unsigned short texture_value(string_iterator_t *it, float *value) {
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

texture_t *new_texture(const char *reffering_line) {
  texture_t         *self = NULL;
  string_iterator_t *it   = new_string_iterator(reffering_line,
                                                TEXTURE_DELIMITERS);
  unsigned short    do_u;
  float             u;
  unsigned short    do_v;
  float             v;
  unsigned short    do_w;
  float             w;

  do_u = texture_value(it, &u);
  next_string_iterator(it);
  do_v = texture_value(it, &v);
  next_string_iterator(it);
  do_w = texture_value(it, &w);

  if(do_u && do_v) {
    self = malloc(sizeof(texture_t));

    self->u = u;
    self->v = v;
  }

  if(self != NULL) {
    if(do_w) {
      self->w = w;
    }

    self->is_extended = do_w;
  }

  free_string_iterator(it);
  it = NULL;

  return self;
}

void free_texture(texture_t *self) {
  if(self != NULL) {
    free(self);
  }
}

