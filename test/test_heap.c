#include <stdio.h>

#include "../include/ds_lib/heap.h"

int main () {

  struct heap min_heap, max_heap;

  heap_initialize(&min_heap, 5);
  heap_initialize(&max_heap, 5);

  int arr[5] = {2, 8, 8, 10, 3};

  for (int i = 0; i < 5; i++) {
    min_heap_insert(&min_heap, (struct tagged_atomic) {arr[i], INT});
    max_heap_insert(&max_heap, (struct tagged_atomic) {arr[i], INT});
  }

  printf("Min heap:\n");
  for (int i = 0; i < 5; i++) {
    printf("%d: %d\n", i, min_heap_remove(&min_heap).int_data);
  }

  printf("Max heap:\n");
  for (int i = 0; i < 5; i++) {
    printf("%d: %d\n", i, max_heap_remove(&max_heap).int_data);
  }

  heap_destroy(&min_heap);
  heap_destroy(&max_heap);
}
