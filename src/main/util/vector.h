/*!
 * \file    vector.h
 * \brief   A container which provide a dynamique array and the behavior of an
 *          array (acces, insertion, etc.).
 *          To provide a generic storage, each elements are stored as a void *.
 * \warning Only the used functions are implemented.
 *
 * \author  Adrien Bougouin <adrien.bougouin@gmail.com>
 */

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdlib.h>

//==============================================================================
// Types
//==============================================================================

/*!
 * \brief The definition of a generic vector.
 *
 * \var   elements    The elements contains by the vector.
 * \var   nb_elements The number of elements in the container.
 * \var   size        The allocated size of the vector.
 */
typedef struct vector_st {
  void    **elements;
  size_t  nb_elements;
  size_t  size;
} vector_t;

//==============================================================================
// Function prototypes
//==============================================================================

/*!
 * \brief   Creation and allocation of an empty vector.
 *
 * \param   initial_size  The initial_size of the container.
 * \return  An allocated and initialized vector.
 */
vector_t *new_vector(size_t initial_size);

/*!
 * \brief Deletion of a vector.
 *
 * \param self The vector to delete.
 */
void free_vector(vector_t *self);

/*!
 * \brief   Test if a vector is empty.
 *
 * \param   self  The vector to test.
 * \return  True if the vector is empty, else False.
 */
int is_empty_vector(vector_t *self);

/*!
 * \brief Add an element to a vector.
 *
 * \param self    The vector which will contain the element.
 * \prama element The element to store.
 */
void add_to_vector(vector_t *self, void *element);

/*!
 * \brief   Access to an element of a vector.
 *
 * \param   self  The vector to access.
 * \param   index The index of the wanted element.
 * \return  The element contain at the index. If there is no element or if the
 *          index is out of range the element is NULL.
 */
void *item_of_vector(vector_t *self, size_t index);

#endif // __VECTOR_H__

