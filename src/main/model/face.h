/*!
 * \file    face.h
 * \brief   Definition of .obj file face.
 * \warning It doesn't include the texture coordinates, but file with those is
 *          compatible.
 *
 * \author  Adrien Bougouin <adrien.bougouin@gmail.com>
 */

#ifndef __FACE_H__
#define __FACE_H__

#include "../util/vector.h"

//==============================================================================
// Constants
//==============================================================================

#define MAIN_DELIMITERS "f "
#define SUB_DELIMITER   "/"

#define MINIMAL_POINTS  3

//==============================================================================
// Types
//==============================================================================

/*!
 * \brief   The definition of face wich can have points potentioly associated
 *          with normals.
 * \warning If there is one point with a normal, the other points must have a
 *          normal too.
 *
 * \var     vertexes  The points representing the face.
 * \var     textures  The texturess associated to the points. It could be a NULL
 *                    vector.
 * \var     normals   The normals associated to the points. It could be a NULL
 *                    vector.
 */
typedef struct face_st {
  vector_t *vertexes;
  vector_t *textures;
  vector_t *normals;
} face_t;

//==============================================================================
// Function prototypes
//==============================================================================

/*!
 * \brief   Creation and allocation of a face, reffering to a description line.
 *
 * \param   reffering_line  The string description of the face.
 * \return  The face associated to the reffering line. If the line description
 *          is wrong the result value is NULL.
 */
face_t *new_face(const char *reffering_line);

/*!
 * \brief Deletion of a face.
 *
 * \param The face to delete.
 */
void free_face(face_t *self);

#endif // __FACE_H__

