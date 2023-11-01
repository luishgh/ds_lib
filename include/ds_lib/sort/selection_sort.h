#ifndef _DS_LIB_SELECTION_H
#define _DS_LIB_SELECTION_H

#include "../types.h"

/**
   Selection sort.

   Stable: no
   Adaptable:
   Time Complexity: O(n^2)
   Space Complexity: O(1)
 */

static inline void selection_sort(struct tagged_atomic *data, unsigned n) {
  unsigned i, j, min_idx;
  struct tagged_atomic old_i;

  for (i = 0; i < n - 1; i++) {
    min_idx = i;

    for (j = i+1; j < n; j++) {
      if (compare_atomic(data[j], data[min_idx])) min_idx = j;
    }

    if (min_idx != i) {
      old_i = data[i];
      data[i] = data[min_idx];
      data[min_idx] = old_i;
    }
  }
}

#endif /* _DS_LIB_SELECTION_H */
