#include <stdio.h>
#include "../include/ds_lib/deque.h"

int main() {

  union atomic_data arr[] = {1, 2, 3};

  struct deque q;
  deque_initialize(&q);

  // test using as a queue

  for (int i = 0; i < 3; i++) deque_push_back(&q, arr[i]);

  while (!deque_empty(&q)) {
    printf("%d ", deque_front(&q).int_data);
    deque_pop(&q);
  }
  printf("\n");

  // test using as a stack
  
  for (int i = 0; i < 3; i++) deque_push_front(&q, arr[i]);

  while (!deque_empty(&q)) {
    printf("%d ", deque_front(&q).int_data);
    deque_pop(&q);
  }
  printf("\n");

  deque_destroy(&q);
  
  return 0;
}
