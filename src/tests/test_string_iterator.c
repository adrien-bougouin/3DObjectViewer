#include <stdio.h>
#include <stdlib.h>

#include "../main/util/string_iterator.h"

int main(int argc, char ** argv) {
  printf("Creation of a string iterator\n\n");
  string_iterator_t *it = new_string_iterator("This is an iterator test.",
                                              " .");

  printf("Use the iterator to browse a string:\n\n");
  while(it->good) {
    printf("%s\n", it->current_string);
    next_string_iterator(it);
  }

  printf("\nDeletion of the string iterator\n");
  free_string_iterator(it);
  it = NULL;

  return 0;
}

