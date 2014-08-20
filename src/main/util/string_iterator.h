/*!
 * \file    string_iterator.h
 * \brief   A structure used to browse a string. Its an unidirectional iterator.
 *
 * \author  Adrien Bougouin <adrien.bougouin@gmail.com>
 */

#ifndef __STRING_ITERATOR_H__
#define __STRING_ITERATOR_H__

//==============================================================================
// Types
//==============================================================================

/*!
 * \brief A unidirectional iterator on a string.
 *
 * \var   source          The string to browse.
 * \var   delimiters      The set of delimiters used to browse the string.
 * \var   current_string  The current string.
 * \var   next_position   The beginning of the next string.
 * \var   good            Indicate wether the iterator is at end or not.
 */
typedef struct string_iterator_st {
  char            *source;
  char            *delimiters;
  char            *current_string;
  size_t          next_position;
  unsigned short  good;
} string_iterator_t;

//==============================================================================
// Function prototypes
//==============================================================================

/*!
 * \brief   Creation and allocation of an iterator on a source string delimiting
 *          by a set of characters.
 *
 * \param   source      The source string to browse.
 * \param   delimiters  A string representing a set of delimiters.
 * \return  An allocated and initialized string iterator.
 */
string_iterator_t *new_string_iterator(const char *source,
                                       const char *delimiters);

/*!
 * \brief Deletion of a string iterator.
 *
 * \param self  The string iterator to delete.
 */
void free_string_iterator(string_iterator_t *self);

/*!
 * \brief Browse a string.
 *
 * \param self The string operator to use for browsing.
 */
string_iterator_t *next_string_iterator(string_iterator_t *self);

#endif // __STRING_ITERATOR_H__

