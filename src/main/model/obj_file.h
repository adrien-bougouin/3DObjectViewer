/*!
 * \file    obj_file.h
 * \brief   Description of a file in the .obj format.
 *
 * \author  Adrien Bougouin <adrien.bougouin@gmail.com>
 */

#ifndef __OBJ_FILE_H__
#define __OBJ_FILE_H__

#include "../util/vector.h"

//==============================================================================
// Constants
//==============================================================================

// keywords
#define COMMENT_KEYWORD     "#"
#define OBJECT_KEYWORD      "o "
#define GROUP_KEYWORD       "g "
#define VERTEX_KEYWORD      "v "
#define TEXTURE_KEYWORD     "vt "
#define NORMAL_KEYWORD      "vn "
#define FACE_KEYWORD        "f "

#define NB_OBJ_FILE_COLUMN  65536

//==============================================================================
// Types
//==============================================================================

/*!
 * \brief The parsing result of a file in the .obj format.
 *
 * \var   name    The name of the .obj file.
 * \var   objects The objects defined in the .obj file.
 */
typedef struct obj_file_st {
  char      *name;
  vector_t  *objects;
} obj_file_t;

/*!
 * \brief A .obj file load when needed.
 *
 * \var   filename  The file used to create the instance.
 * \var   obj_file  The instance of the .obj file.
 */
typedef struct lazy_obj_file_st {
  char        *filename;
  obj_file_t  *obj_file;
} lazy_obj_file_t;

//==============================================================================
// Function prototypes
//==============================================================================

/*!
 * \brief   Creation and allocation of a .obj file.
 *
 * \param   filename  The description file.
 * \return  The allocated and initialized .obj file.
 */
obj_file_t *new_obj_file(const char *filename);

/*!
 * \brief Deletion of a .obj file.
 *
 * \param The .obj file to delete.
 */
void free_obj_file(obj_file_t *self);

/*!
 * \brief Display all the objects described in a .obj file.
 *
 * \param self    The .obj file.
 */
void display_obj_file(obj_file_t  *self);

/*!
 * \brief   Creation and allocation of a lazy loading .obj file.
 *
 * \param   filename  The description file.
 * \return  The allocated and initialized lazy .obj file.
 */
lazy_obj_file_t *new_lazy_obj_file(const char *filename);

/*!
 * \brief Deletion of a lazy .obj file.
 *
 * \param The lazy .obj file to delete.
 */
void free_lazy_obj_file(lazy_obj_file_t *self);

/*!
 * \brief   Access to the instance stored by a lazy .obj file.
 *
 * \param   self  The lazy .obj file.
 * \return  The .obj file stored.
 */
obj_file_t *get_obj_file_instance(lazy_obj_file_t *self);

#endif // __OBJ_FILE_H__

