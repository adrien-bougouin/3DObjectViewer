/*!
 * \file    texture.h
 * \brief   A texture coordinate created with an .obj description :
 *            "vt 1.0 0.0"
 *            "vt 1.0 0.0 0.0"
 *
 * \author  Adrien Bougouin <adrien.bougouin@gmail.com>
 */

#ifndef __TEXTURE_H__
#define __TEXTURE_H__

//==============================================================================
// Constants
//==============================================================================

#define TEXTURE_DELIMITERS "vt "

//==============================================================================
// Types
//==============================================================================

/*!
 * \brief The definition of a potentialy homogeneous coordinate.
 *
 * \var   u
 * \var   v
 * \var   w
 * \var   is_extended True if the texture contains w, else false.
 */
typedef struct texture_st {
  float u;
  float v;
  float w;
  unsigned char is_extended;
} texture_t;

//==============================================================================
// Function prototypes
//==============================================================================

/*!
 * \brief   Creation and allocation of a texture, reffering to a description
 *          line.
 *
 * \param   reffering_line  The string description of the texture.
 * \return  The coordinate associated to the reffering line. If the line
 *          description is wrong the result value is NULL;
 */
texture_t *new_texture(const char *reffering_line);

/*!
 * \brief Deletion of a texture.
 *
 * \param self  The texture to delete.
 */
void free_texture(texture_t *self);

#endif // __TEXTURE_H__

