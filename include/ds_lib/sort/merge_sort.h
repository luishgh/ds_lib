#ifndef _DS_LIG_MERGE_SORT_H
#define _DS_LIG_MERGE_SORT_H

#include "../types.h"

/**
   Merge sort.

   Stable: Yes
   Adaptable: No
   Time Complexity: O(n log n)
   Space Complexity:
 */

static inline void __merge(struct tagged_atomic *data, unsigned begin, unsigned mid, unsigned end) {
  unsigned size_left = mid - begin + 1;
  unsigned size_right = end - mid;

  // Create temp arrays and copy data entries
  struct tagged_atomic left[size_left], right[size_right];
  for (unsigned i = 0; i < size_left; i++)
    left[i] = data[begin + i];
  for (unsigned i = 0; i < size_right; i++)
    right[i] = data[mid + 1 + i];

  // i => idx on left
  // j => idx on right
  // k => idx on data
  unsigned i = 0, j = 0, k = begin;

  // merge left and right back onto data
  while (i < size_left && j < size_right) {
    if (compare_atomic(left[i], right[j])) {
      data[k] = left[i];
      i++;
    } else {
      data[k] = right[j];
      j++;
    }

    k++;
  }

  // copy remaining elements (only one of the while loops will run)
  while (i < size_left) {
    data[k] = left[i];
    i++, k++;
  }
  while (j < size_right) {
    data[k] = right[j];
    j++, k++;
  }

}

static inline void __merge_sort(struct tagged_atomic *data, unsigned begin, unsigned end) {
  if (begin >= end) return; // invalid interval

  // b + (e - b)/2 = (2b + e - b)/2 = (b + e)/2
  unsigned mid = (begin + end) / 2;

  __merge_sort(data, begin, mid);
  __merge_sort(data, mid + 1, end);
  __merge(data, begin, mid, end);
}

static inline void merge_sort(struct tagged_atomic *data, unsigned n) {
  __merge_sort(data, 0, n-1);
}

#endif /* _DS_LIG_MERGE_SORT_H */
