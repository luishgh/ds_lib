#include <stdio.h>

#include "../include/ds_lib/sort/insertion_sort.h"
#include "../include/ds_lib/sort/selection_sort.h"
#include "../include/ds_lib/sort/bubble_sort.h"
#include "../include/ds_lib/sort/heap_sort.h"

int main() {

  struct int_pair a = {1, 2};
  struct int_pair b = {2, 1};
  struct int_pair c = {2, 2};

  struct tagged_atomic arr[] = {{(union atomic_data) c, INT_PAIR}, {(union atomic_data) a, INT_PAIR}, {(union atomic_data) b, INT_PAIR}};

  heap_sort(arr, 3);

  for (int i = 0; i < 3; i++) {
    printf("%i: (%d, %d)\n", i, arr[i].data.int_pair_data.first, arr[i].data.int_pair_data.second);
  }

  return 0;
}
