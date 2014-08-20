/*!
 * \file    string_iterator.h
 *
 * \author  Adrien Bougouin <adrien.bougouin@gmail.com>
 */

#include <stdlib.h>
#include <string.h>

#include "string_iterator.h"

//==============================================================================
// Private functions
//==============================================================================

void next_position(string_iterator_t *self) {
  unsigned short  done    = 0;

  while(self->next_position < strlen(self->source) && !done) {
    unsigned short is_delimiter = 0;

    for(size_t i = 0; i < strlen(self->delimiters); ++i) {

      if(self->source[self->next_position] == self->delimiters[i]) {
        is_delimiter = 1;
      }
    }

    if(!is_delimiter) {
      --(self->next_position);

      done = 1;
    }

    ++(self->next_position);
  }
} 

char *next_string(string_iterator_t *self) {
  char            *result = NULL;
  unsigned short  done  = 0;
  size_t          begin = self->next_position;
  size_t          end   = begin;

  if(self->next_position < strlen(self->source)) {
    while(end < strlen(self->source) && !done) {
      size_t i = 0;

      while(i < strlen(self->delimiters) && !done) {
        if(self->source[end] == self->delimiters[i]) {
          --end;
          --end;
          done = 1;
        }

        ++i;
      }

      ++end;
    }

    result = calloc(((end + 1) - begin) + 1, sizeof(char));

    for(size_t i = 0; i <= end - begin; ++i) {
      result[i] = self->source[begin + i];
    }
    result[(end + 1) - begin] = '\0';

    self->next_position = end + 2;
    next_position(self);
  }

  return result;
}

//==============================================================================
// Public functions
//==============================================================================

string_iterator_t *new_string_iterator(const char *source,
                                       const char *delimiters) {
  string_iterator_t *self = malloc(sizeof(string_iterator_t));

  self->source = calloc(strlen(source) + 1, sizeof(char));
  strcpy(self->source, source);
  self->delimiters = calloc(strlen(delimiters) + 1, sizeof(char));
  strcpy(self->delimiters, delimiters);

  self->next_position   = 0;
  next_position(self);
  self->current_string  = next_string(self);
  self->good            = (self->current_string != NULL);

  return self;
}

void free_string_iterator(string_iterator_t *self) {
  if(self != NULL) {
    free(self->source);
    free(self->current_string);
    free(self->delimiters);
    free(self);
  }
}

string_iterator_t *next_string_iterator(string_iterator_t *self) {
  if(self != NULL) {
    free(self->current_string);

    self->current_string  = next_string(self);
    self->good            = (self->current_string != NULL);
  }

  return self;
}

