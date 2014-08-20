/*!
 * \file    graphical_object.c
 *
 * \author  Adrien Bougouin <adrien.bougouin@gmail.com>
 */

#ifdef __MACH__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <string.h>

#include "graphical_object.h"
#include "coordinate.h"
#include "face.h"

//==============================================================================
// Private functions
//==============================================================================

void display_face(graphical_object_t *self, face_t *face) {
  if(face != NULL) {
    glBegin(GL_POLYGON);

    for(size_t i = 0;
        i < face->vertexes->nb_elements
        && (face->normals == NULL               // FIXME shouldn't be necessary
            || i < face->normals->nb_elements); // FIXME shouldn't be necessary
        ++i) {
      int vertex = *((int *) item_of_vector(face->vertexes, i)) - 1;
      coordinate_t  *v = item_of_vector(self->vertexes, vertex);

      if(face->normals != NULL) {
        int           normal = *((int *) item_of_vector(face->normals, i)) - 1;
        coordinate_t  *vn = item_of_vector(self->normals, normal);

        glNormal3f(vn->x, vn->y, vn->z);
      }

      if(v->is_extended) {
        glVertex4f(v->x, v->y, v->z, v->h);
      } else {
        glVertex3f(v->x, v->y, v->z);
      }
    }

    glEnd();
  }
}

void display_faces(graphical_object_t *self, vector_t *faces) {
  if(faces != NULL) {
    for(size_t i = 0; i < faces->nb_elements; ++i) {
      display_face(self, item_of_vector(faces, i));
    }
  }
}

//==============================================================================
// Public functions
//==============================================================================

graphical_object_t *new_graphical_object(const char *name,
                                         vector_t   *vertexes,
                                         vector_t   *textures,
                                         vector_t   *normals,
                                         vector_t   *faces) {
  graphical_object_t *self = malloc(sizeof(graphical_object_t));

  self->name = calloc(strlen(name) + 1, sizeof(char));
  strcpy(self->name, name);

  self->vertexes  = vertexes;
  self->textures  = textures;
  self->normals   = normals;

  self->faces    = faces;

  return self;
}

void free_graphical_object(graphical_object_t *self) {
  if(self != NULL) {
    free(self->name);
    free_vector(self->vertexes);
    free_vector(self->textures);
    free_vector(self->normals);
    free_vector(self->faces);
    free(self);
  }
}

void display_graphical_object(graphical_object_t *self) {
  if(self != NULL) {
    display_faces(self, self->faces);
  }
}

