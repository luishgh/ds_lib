#include <stdio.h>
#include "../include/ds_lib/list.h"

int main() {

  union atomic_data arr[] = {1, 2, 3};

  struct list l;
  list_initialize(&l, arr, 3);

  int i; struct list* pos;
  list_for_each(i, pos, &l) {
    printf("%d: %d\n", i, pos->data.int_data);
  }

  list_destroy(&l);
  
  return 0;
}
