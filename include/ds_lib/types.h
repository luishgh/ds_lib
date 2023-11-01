#ifndef _DS_LIB_TYPES_H
#define _DS_LIB_TYPES_H

#include <assert.h>

// Author: Luis Henrique Gomes Higino

/*
  General type definitions.
*/

struct int_pair {
  int first;
  int second;
};

//! Union type for atomic data types, generally containers will use it.
union atomic_data {
  int int_data;
  float float_data;
  struct int_pair int_pair_data;
};

enum tag {INT, FLOAT, INT_PAIR};

//! Tagged union for atomic data types
struct tagged_atomic {
  union atomic_data data;
  enum tag tag;
};

//! Returns whether x <= y
static inline int compare_atomic(struct tagged_atomic x, struct tagged_atomic y) {
  assert(x.tag == y.tag);

  if (x.tag == INT) return x.data.int_data <= y.data.int_data;
  else if (x.tag == FLOAT) return x.data.float_data <= y.data.float_data;
  else if (x.tag == INT_PAIR) {
    if (x.data.int_pair_data.first == y.data.int_pair_data.first)
      return x.data.int_pair_data.second <= y.data.int_pair_data.second;
    else return x.data.int_pair_data.first < y.data.int_pair_data.first;
  }
  else assert(0);
}


#endif /* _DS_LIB_TYPES_H */
