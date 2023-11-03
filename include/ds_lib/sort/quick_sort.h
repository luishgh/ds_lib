#ifndef _DS_LIB_QUICK_SORT_H
#define _DS_LIB_QUICK_SORT_H

#include "../types.h"

/**
   Quick sort.

   Stable: No
   Adaptable: No
   Time Complexity: O(n^2), average O(n log n)
   Space Complexity: O(1)
 */

static inline void __quick_partition(struct tagged_atomic *data, int *i, int *j) {
  // choose the pivot (middle element in this implementation)
  unsigned pivot_idx = (*i + *j)/2;
  struct tagged_atomic pivot = data[pivot_idx];
  
  do {
    // find element bigger then pivot on left
    while (!compare_atomic(pivot, data[*i])) (*i)++;
    // find element smaller then pivot on right
    while (*j != pivot_idx && compare_atomic(pivot, data[*j])) (*j)--;

    // swap elements and proceed to next positions
    if (*i <= *j) {
      struct tagged_atomic aux = data[*i];
      data[*i] = data[*j];
      data[*j] = aux;
      (*i)++, (*j)--;
    }
  } while (*i <= *j);
}

static inline void __quick_sort(struct tagged_atomic *data, unsigned begin, unsigned end) {
  int i = begin, j = end;
  __quick_partition(data, &i, &j);
  if (begin < j) __quick_sort(data, begin, j);
  if (i < end) __quick_sort(data, i, end);
}

static inline void quick_sort(struct tagged_atomic *data, unsigned n) {
  __quick_sort(data, 0, n-1);
}

#endif /* _DS_LIB_QUICK_SORT_H */
