#ifndef _DS_LIB_DEQUE_H
#define _DS_LIB_DEQUE_H

// Author: Luis Henrique Gomes Higino

#include <assert.h>
#include <stdlib.h>

#include "list.h"
#include "types.h"

/*
  Simple deque implementation.

  This can also be used as a stack or a queue:
  - stack: use push_front for pushing items
  - queue: use push_back for pushing items

  Complexities:
  deque_push_back: O(1)
  deque_push_front: O(1)
  deque_front: O(1)
  deque_pop: O(1)
 */

struct deque {
  struct list * list;
};

static inline void deque_initialize(struct deque *q) {
  q->list = (struct list*) malloc(sizeof (struct list));
  init_list_head(q->list);
}

/**
   @brief push entry with @d at the end
   @param q deque to insert
   @param d data to push

   Complexity: O(1)
 */
static inline void deque_push_back(struct deque *q, union atomic_data d) {
  list_push_back(d, q->list);
}

/**
   @brief push entry with @d at the start
   @param q deque to insert
   @param d data to push

   Complexity: O(1)
 */
static inline void deque_push_front(struct deque *q, union atomic_data d) {
  list_push_front(d, q->list);
}

/**
   @brief access first element
   @param q deque to access

   Complexity: O(1)
 */
static inline union atomic_data deque_front(struct deque *q) {
  return list_front(q->list)->data;
}

/**
   @brief remove first element form @q
   @param q deque to modify

   Complexity: O(1)
 */
static inline void deque_pop(struct deque *q) {
  struct list *cur_top = list_front(q->list);
  list_del(cur_top);
  free(cur_top);
}

/**
   @brief check if @q is empty
   @param q deque to check

   Complexity: O(1)
 */
static inline int deque_empty(struct deque *q) {
  return list_empty(q->list);
}

/**
   @brief Deallocate memory inside @q
   @param q deque to destroy

   Complexity: O(n)
*/
static inline void deque_destroy(struct deque *q) {
  if (!list_empty(q->list)) list_destroy(q->list);

  free(q->list);
}

#endif /* _DS_LIB_DEQUE_H */
