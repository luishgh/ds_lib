#ifndef _DS_LIB_HEAP_H
#define _DS_LIB_HEAP_H

#include <stdlib.h>
#include "./types.h"

// TODO: add dynamic size heaps

struct heap {
  unsigned size;
  struct tagged_atomic * data;
};

static inline void heap_initialize(struct heap *h, unsigned size) {
  h->data = (struct tagged_atomic *) malloc(sizeof(struct tagged_atomic) * size);
  h->size = 0;
} 

static inline void heap_destroy(struct heap *h) {
  free(h->data);
}

static inline unsigned __get_ancestor_idx(unsigned pos) {
  return (pos-1)/2;
}

static inline unsigned __get_successor_left_idx(unsigned pos) {
  return 2 * pos + 1;
}

static inline unsigned __get_successor_right_idx(unsigned pos) {
  return 2 * pos + 2;
}

static inline void __swap_nodes(struct heap *h, unsigned x, unsigned y) {
  const struct tagged_atomic aux = h->data[x];
  h->data[x] = h->data[y];
  h->data[y] = aux;
}

static inline int heap_empty(const struct heap *h) {
  return h->size == 0;
}

static inline int __get_min_suc_idx(const struct heap *h, unsigned pos) {
  // node has no children
  if (__get_successor_left_idx(pos) >= h->size) return -1;

  // node only has one child
  if (__get_successor_right_idx(pos) >= h->size) {
    return __get_successor_left_idx(pos);
  }

  // general case: 2 children
  int suc_left = __get_successor_left_idx(pos);
  int suc_right = __get_successor_right_idx(pos);
  int min_idx = compare_atomic(h->data[suc_left], h->data[suc_right]) ? suc_left : suc_right;

  return min_idx;
}

static inline int __get_max_suc_idx(const struct heap *h, unsigned pos) {
  // node has no children
  if (__get_successor_left_idx(pos) >= h->size) return -1;

  // node only has one child
  if (__get_successor_right_idx(pos) >= h->size) {
    return __get_successor_left_idx(pos);
  }

  // general case: 2 children
  int suc_left = __get_successor_left_idx(pos);
  int suc_right = __get_successor_right_idx(pos);
  int max_idx = !compare_atomic(h->data[suc_left], h->data[suc_right]) ? suc_left : suc_right;

  return max_idx;
}

static inline void min_heap_insert(struct heap *h, struct tagged_atomic x) {
  if (heap_empty(h)) {
    h->data[0] = x;
  } else {
    h->data[h->size] = x;
    unsigned pos = h->size;

    while (pos != 0 && compare_atomic(h->data[pos], h->data[__get_ancestor_idx(pos)])) {
      __swap_nodes(h, pos, __get_ancestor_idx(pos));
      pos = __get_ancestor_idx(pos);
    }
  }

  h->size++;
}

static inline void max_heap_insert(struct heap *h, struct tagged_atomic x) {
  if (heap_empty(h)) {
    h->data[0] = x;
  } else {
    h->data[h->size] = x;
    unsigned pos = h->size;

    while (pos != 0 && !compare_atomic(h->data[pos], h->data[__get_ancestor_idx(pos)])) {
      __swap_nodes(h, pos, __get_ancestor_idx(pos));
      pos = __get_ancestor_idx(pos);
    }
  }

  h->size++;
}

static inline void __min_heapify(struct heap * h) {
  unsigned pos = 0;
  int min_idx = __get_min_suc_idx(h, 0);
  while (min_idx != -1 && !compare_atomic(h->data[pos], h->data[min_idx])) {
    __swap_nodes(h, pos, min_idx);
    pos = min_idx;
    min_idx = __get_min_suc_idx(h, pos);
  }
}

static inline void __max_heapify(struct heap * h) {
  unsigned pos = 0;
  int max_idx = __get_max_suc_idx(h, 0);
  while (max_idx != -1 && compare_atomic(h->data[pos], h->data[max_idx])) {
    __swap_nodes(h, pos, max_idx);
    pos = max_idx;
    max_idx = __get_max_suc_idx(h, pos);
  }
}

// type = 0 => min
// type = 1 => max
static inline union atomic_data __heap_remove(struct heap * h, unsigned type) {
  union atomic_data ret = h->data[0].data;

  __swap_nodes(h, 0, h->size-1); // swap root with last element
  h->size--; // remove last element

  if (!type) __min_heapify(h);
  else __max_heapify(h);

  return ret;
}

static inline union atomic_data min_heap_remove(struct heap *h) {
  return __heap_remove(h, 0);
}

static inline union atomic_data max_heap_remove(struct heap *h) {
  return __heap_remove(h, 1);
}

#endif /* _DS_LIB_HEAP_H */
