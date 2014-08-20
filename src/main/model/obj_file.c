/*!
 * \file    obj_file.c
 *
 * \author  Adrien Bougouin <adrien.bougouin@gmail.com>
 */

#ifdef __MACH__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "obj_file.h"
#include "graphical_object.h"
#include "face.h"
#include "coordinate.h"
#include "texture.h"
#include "../util/string_iterator.h"

//==============================================================================
// Private types
//==============================================================================

typedef enum line_type_e {
  UNKNOWN_TYPE,
  COMMENT_TYPE,
  OBJECT_TYPE,
  GROUP_TYPE,
  VERTEX_TYPE,
  TEXTURE_TYPE,
  NORMAL_TYPE,
  FACE_TYPE,
} line_type_t;

//==============================================================================
// Private functions
//==============================================================================

char *read_line(FILE *file) {
  char   *line = calloc(NB_OBJ_FILE_COLUMN, sizeof(char));
  size_t size;

  fgets(line, NB_OBJ_FILE_COLUMN, file);
  size = strlen(line);
  
  // delete the useless carriage return
  if(size != 0 && line[size - 1] == '\n') {
    line[size - 1] = '\0';
  }

  return line;
}

char *extract_name(const char *line) {
  char              *name = NULL;
  string_iterator_t *it   = new_string_iterator(line, "go ");

  next_string_iterator(it);

  if(it->good) {
    name = calloc(strlen(it->current_string) + 1, sizeof(char));

    strcpy(name, it->current_string);
  }

  free_string_iterator(it);

  return name;
}

unsigned short begin_with(const char *line, const char *keyword) {
  return (strncmp(line, keyword, strlen(keyword)) == 0);
}

line_type_t type_of_line(const char *line) {
  line_type_t type = UNKNOWN_TYPE;

  if(begin_with(line, COMMENT_KEYWORD)) {
    type = COMMENT_TYPE;
  } else if(begin_with(line, OBJECT_KEYWORD)) {
    type = OBJECT_TYPE;
  } else if(begin_with(line, GROUP_KEYWORD)) {
    type = GROUP_TYPE;
  } else if(begin_with(line, VERTEX_KEYWORD)) {
    type = VERTEX_TYPE;
  } else if(begin_with(line, TEXTURE_KEYWORD)) {
    type = TEXTURE_TYPE;
  } else if(begin_with(line, NORMAL_KEYWORD)) {
    type = NORMAL_TYPE;
  } else if(begin_with(line, FACE_KEYWORD)) {
    type = FACE_TYPE;
  }

  return type;
}

void parse_obj_file(obj_file_t *self) {
  FILE *obj_file = fopen(self->name, "r");

  if(obj_file != NULL) {
    char            *name     = NULL;
    vector_t        *vertexes = NULL;
    vector_t        *textures = NULL;
    vector_t        *normals  = NULL;
    vector_t        *faces    = NULL;

    while(!feof(obj_file)) {
      char *line = read_line(obj_file);

      switch(type_of_line(line)) {
        // creation of the previous object
        case OBJECT_TYPE:
          // is there a previous object
          if(vertexes != NULL
             && faces != NULL) {
            if(self->objects == NULL) {
              self->objects = new_vector(4);
            }

            if(name == NULL) {
              name = calloc(8, sizeof(char));

              strcpy(name, "no name");
            }

            add_to_vector(self->objects, new_graphical_object(name,
                                                              vertexes,
                                                              textures,
                                                              normals,
                                                              faces));
            free(name);

            name      = extract_name(line);
            vertexes  = NULL;
            textures  = NULL;
            normals   = NULL;
            faces     = NULL;
          }
        break;

        case VERTEX_TYPE:
          if(vertexes == NULL) {
            vertexes = new_vector(10);
          }

          add_to_vector(vertexes, new_coordinate(line));
        break;

        case TEXTURE_TYPE:
          if(textures == NULL) {
            textures = new_vector(10);
          }

          add_to_vector(textures, new_texture(line));
        break;

        case NORMAL_TYPE:
          if(normals == NULL) {
            normals = new_vector(10);
          }

          add_to_vector(normals, new_coordinate(line));
        break;

        case FACE_TYPE:
          if(faces == NULL) {
            faces = new_vector(10);
          }

          add_to_vector(faces, new_face(line));
        break;

        default:
        break;
      }

      free(line);
    }

    // is there a last graphical object
    if(vertexes != NULL
       && faces != NULL) {
      if(self->objects == NULL) {
        self->objects = new_vector(2);
      }

      if(name == NULL) {
        name = calloc(8, sizeof(char));

        strcpy(name, "no name");
      }

      add_to_vector(self->objects, new_graphical_object(name,
                                                        vertexes,
                                                        textures,
                                                        normals,
                                                        faces));
      free(name);
    }

    fclose(obj_file);
  }
}

//==============================================================================
// Public functions
//==============================================================================

obj_file_t *new_obj_file(const char *filename) {
  obj_file_t *self = malloc(sizeof(obj_file_t));

  self->name    = calloc(strlen(filename) + 1, sizeof(char));
  self->objects = NULL;

  strcpy(self->name, filename);

  parse_obj_file(self);

  return self;
}

void free_obj_file(obj_file_t *self) {
  if(self != NULL) {
    free(self->name);
    free_vector(self->objects);
    free(self);
  }
}

void display_obj_file(obj_file_t  *self) {
  if(self != NULL && self->objects != NULL) {
    glPushMatrix();

    for(size_t i = 0; i < self->objects->nb_elements; ++i) {
      display_graphical_object(item_of_vector(self->objects, i));
    }

    glPopMatrix();
  }
}

lazy_obj_file_t *new_lazy_obj_file(const char *filename) {
  lazy_obj_file_t *self = NULL;

  if(filename != NULL) {
    self = malloc(sizeof(lazy_obj_file_t));

    self->filename = calloc(strlen(filename) + 1, sizeof(char));
    self->obj_file = NULL;

    strcpy(self->filename, filename);
  }

  return self;
}

void free_lazy_obj_file(lazy_obj_file_t *self) {
  free(self->filename);
  self->filename = NULL;
  free_obj_file(self->obj_file);
  self->obj_file = NULL;
  free(self);
}

obj_file_t *get_obj_file_instance(lazy_obj_file_t *self) {
  if(self != NULL) {
    if(self->obj_file == NULL) {
      self->obj_file = new_obj_file(self->filename);
    }

    return self->obj_file;
  }

  return NULL;
}

