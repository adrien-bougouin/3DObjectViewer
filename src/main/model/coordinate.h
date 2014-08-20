/*!
 * \file    coordinate.h
 * \brief   A 3D coordinate. It could be an homogeneous coordinate.
 *          The coordinate is created with an .obj description :
 *            "v  1.0 0.0 0.0 1.0"
 *            "v  1.0 0.0 0.0"
 *            "vn 1.0 0.0 0.0"
 *
 * \author  Adrien Bougouin <adrien.bougouin@gmail.com>
 */

#ifndef __COORDINATE_H__
#define __COORDINATE_H__

//==============================================================================
// Constants
//==============================================================================

#define COORDINATE_DELIMITERS "vn "

//==============================================================================
// Types
//==============================================================================

/*!
 * \brief The definition of a potentialy homogeneous coordinate.
 *
 * \var   x
 * \var   y
 * \var   z
 * \var   h           The scale factor.
 * \var   is_extended True if the coordinate contains a scale factor, else
 *                    false.
 */
typedef struct coordinate_st {
  float x;
  float y;
  float z;
  float h;
  unsigned char is_extended;
} coordinate_t;

//==============================================================================
// Function prototypes
//==============================================================================

/*!
 * \brief   Creation and allocation of a coordinate, reffering to a description
 *          line.
 *
 * \param   reffering_line  The string description of the coordinate.
 * \return  The coordinate associated to the reffering line. If the line
 *          description is wrong the result value is NULL;
 */
coordinate_t *new_coordinate(const char *reffering_line);

/*!
 * \brief Deletion of a coordinate.
 *
 * \param self  The coordinate to delete.
 */
void free_coordinate(coordinate_t *self);

#endif // __COORDINATE_H__

