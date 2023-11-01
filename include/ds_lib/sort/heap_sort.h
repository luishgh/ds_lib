#ifndef _DS_LIB_HEAP_SORT_H
#define _DS_LIB_HEAP_SORT_H

#include "../heap.h"

/**
   Heap sort.

   Stable:
   Adaptable:
   Time Complexity:
   Space Complexity:
 */

static inline void heap_sort(struct tagged_atomic *data, unsigned n) {
  struct heap min_heap;
  heap_initialize(&min_heap, n);
  enum tag data_tag = data[0].tag;

  for (unsigned i = 0; i < n; i++) {
    min_heap_insert(&min_heap,  data[i]);
  }

  for (unsigned i = 0; i < n; i++) {
    data[i] = (struct tagged_atomic) {min_heap_remove(&min_heap), data_tag};
  }

  heap_destroy(&min_heap);
}

#endif /* _DS_LIB_HEAP_SORT_H */
