#ifndef _DS_LIB_TYPES_H
#define _DS_LIB_TYPES_H

// Author: Luis Henrique Gomes Higino

/*
  General type definitions.
*/

//! Union type for atomic data types, generally containers will use it.
union atomic_data {
  int int_data;
  float float_data;
};

#endif /* _DS_LIB_TYPES_H */
