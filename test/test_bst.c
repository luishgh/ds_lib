#include <stdio.h>

#include "../include/ds_lib/trees/bst.h"

int main() {

  union atomic_data arr[] = {42, 3, 1, 5, 2, 4};

  struct node tree;
  bst_initialize(&tree);

  for (int i = 0; i < 6; i++) {
    bst_insert(&tree, arr[i], INT);
  }

  printf("max: %d\nmin: %d\n", bst_max(&tree).int_data, bst_min(&tree).int_data);

  int found_10 =  bst_search(&tree, (union atomic_data) 10, INT);
  int found_42=  bst_search(&tree, (union atomic_data) 42, INT);
  printf("search 10: %d\nsearch 42: %d\n", found_10, found_42);

  return 0;
}
