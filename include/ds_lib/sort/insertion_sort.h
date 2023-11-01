#ifndef _DS_LIB_INSERTION_H
#define _DS_LIB_INSERTION_H

#include "../types.h"

/**
   Insertion sort.

   Stable: 
   Adaptable:
   Time Complexity: O(n^2)
   Space Complexity: O(1)
 */

static inline void insertion_sort(struct tagged_atomic *data, unsigned n) {
  int i, j;
  struct tagged_atomic key;

  for (i = 1; i < n; i++) {
    key = data[i];
    j = i - 1;

    while (j >= 0 && !(compare_atomic(data[j], key))) {
      data[j + 1] = data[j];
      j = j - 1;
    }

    data[j + 1] = key;
  }
}

#endif /* _DS_LIB_INSERTION_H */
