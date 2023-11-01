#ifndef _DS_LIB_BUBBLE_H
#define _DS_LIB_BUBBLE_H

#include "../types.h"

/**
   Bubble sort.

   Stable: Yes
   Adaptable:
   Time Complexity: O(n^2)
   Space Complexity: O(1)
 */

static inline void bubble_sort(struct tagged_atomic *data, unsigned n) {
  int swapped;
  struct tagged_atomic aux;

  for (unsigned i = 0; i < n - 1; i++) {
    swapped = 0;
    
    for (unsigned j = 0; j < n-1; j++) {
      if (!compare_atomic(data[j], data[j+1])) {
        aux = data[j];
        data[j] = data[j+1];
        data[j+1] = aux;
        swapped = 1;
      }
    }

    if (!swapped) break;
  }

}

#endif /* _DS_LIB_BUBBLE_H */
