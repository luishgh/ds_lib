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
 */

struct deque {
  struct list * list;
};

static inline void deque_initialize(struct deque *q) {
  q->list = (struct list*) malloc(sizeof (struct list));
  init_list_head(q->list);
}

static inline void deque_push_back(struct deque *q, union atomic_data d) {
  list_push_back(d, q->list);
}

static inline void deque_push_front(struct deque *q, union atomic_data d) {
  list_push_front(d, q->list);
}

static inline void deque_pop(struct deque *q) {
  struct list *cur_top = list_front(q->list);
  list_del(cur_top);
  free(cur_top);
}

static inline union atomic_data deque_front(struct deque *q) {
  return list_front(q->list)->data;
}

static inline int deque_empty(struct deque *q) {
  return list_empty(q->list);
}

static inline void deque_destroy(struct deque *q) {
  if (!list_empty(q->list)) list_destroy(q->list);

  free(q->list);
}

#endif /* _DS_LIB_DEQUE_H */
