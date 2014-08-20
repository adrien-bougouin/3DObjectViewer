/*!
 * \file    graphical_object.h
 * \brief   Representation of a 3D object. This representation is made by a .obj
 *          file.
 *
 * \author  Adrien Bougouin <adrien.bougouin@gmail.com>
 */

#ifndef __GRAPHICAL_OBJECT_H__
#define __GRAPHICAL_OBJECT_H__

#include "../util/vector.h"

//==============================================================================
// Types
//==============================================================================

/*!
 * \brief A 3D object representing by a set o faces.
 *
 * \var   name            The name of the object.
 * \var   vertexes        All the points used for the object.
 * \var   textures        All the textures coordinates used for the object.
 * \var   normals         All the normals used for the object.
 * \var   no_smooth_faces All the faces of the object which don't need to be
 *                        smooth.
 * \var   smooth_faces    All the faces of the object which need to be smooth.
 */
typedef struct graphical_object_st {
  char      *name;
  vector_t  *vertexes;
  vector_t  *textures;
  vector_t  *normals;
  vector_t  *faces;
} graphical_object_t;

//==============================================================================
// Function prototypes
//==============================================================================

/*!
 * \brief   Creation and allocation of a graphical object.
 *
 * \param   name              The name of the object.
 * \param   vertexes          The points of the object.
 * \param   textures          The textures coordinates of the object.
 * \param   normals           The normals of the object.
 * \param   faces             The smooth faces of the object.
 * \return  Ann allocated and initialized object.
 */
graphical_object_t *new_graphical_object(const char *name,
                                         vector_t   *vertexes,
                                         vector_t   *textures,
                                         vector_t   *normals,
                                         vector_t   *faces);

/*!
 * \brief Deletion of a graphical object.
 *
 * \param The graphical object to delete.
 */
void free_graphical_object(graphical_object_t *self);

/*!
 * \brief Display a graphical object.
 *
 * \param The graphical object to display.
 */
void display_graphical_object(graphical_object_t *self);

#endif

