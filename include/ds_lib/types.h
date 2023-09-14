#ifndef _DS_LIB_TYPES_H
#define _DS_LIB_TYPES_H

#include <assert.h>

// Author: Luis Henrique Gomes Higino

/*
  General type definitions.
*/

//! Union type for atomic data types, generally containers will use it.
union atomic_data {
  int int_data;
  float float_data;
};

enum tag {INT, FLOAT};

//! Tagged union for atomic data types
struct tagged_atomic {
  union atomic_data data;
  enum tag tag;
};

static inline int compare_atomic(struct tagged_atomic x, struct tagged_atomic y) {
  assert(x.tag == y.tag);

  if (x.tag == INT) return x.data.int_data <= y.data.int_data;
  else if (x.tag == FLOAT) return x.data.float_data <= y.data.float_data;
  else assert(0);
}


#endif /* _DS_LIB_TYPES_H */
