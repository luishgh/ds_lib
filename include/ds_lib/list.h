#ifndef _DS_LIB_LIST_H
#define _DS_LIB_LIST_H

// Author: Luis Henrique Gomes Higino

#include <assert.h>
#include <stdlib.h>

#include "types.h"


/*
  Doubly linked list implementation. (Circular)

  Insertion/removal operations are constant. Indexing and initializing are linear.

  Complexities:
  list_push_back: O(1)
  list_push_front: O(1)
  list_front: O(1)
  list_back: O(1)
  list_del: O(1)
  list_initialize: O(n)
  list_at: O(n)
 */

struct list {
  union atomic_data data;
  struct list * next;
  struct list * prev;
};

static inline void init_list_head(struct list *head) {
  head->next = head;
  head->prev = head;
  head->data = (union atomic_data) 0;
}

/*
  Emplace new entry with @data between @prev and @next.
*/
static inline void __list_add_between(union atomic_data data, struct list *prev, struct list *next) {
  struct list * new_entry = (struct list*) malloc(sizeof (struct list));
  new_entry->data = data, new_entry->prev = prev, new_entry->next = next;
  next->prev = new_entry;
  prev->next = new_entry;
}

/**
   @brief access first entry
   @param head head of list

   Complexity: O(1)
 */
static inline struct list* list_front(struct list *head) {
  return head->next;
}

/**
   @brief access last entry
   @param head head of list

   Complexity: O(1)
 */
static inline struct list* list_back(struct list *head) {
  return head->prev;
}

/**
   @brief add new entry with @data after @prev
   @param: new_entry new entry to be added
   @param prev the entry to add it after

   Complexity: O(1)
*/
static inline void list_add(union atomic_data data, struct list *prev) {
  __list_add_between(data, prev, prev->next);
}

/**
   @brief add @new_entry to list before @next
   @param: new_entry new entry to be added
   @param next entry to add it before

   Complexity: O(1)
*/
static inline void list_add_before(union atomic_data data, struct list *next) {
  __list_add_between(data, next->prev, next);
}

/**
   @brief add @new_entry at end of list
   @param new_entry entry to be inserted
   @param head head of list

   Complexity: O(1)
*/
static inline void list_push_back(union atomic_data data, struct list *head) {
  list_add_before(data, head);
  head->data.int_data += 1;
}

/**
   @brief add @new_entry at front of list
   @param new_entry entry to be inserted
   @param head head of list

   Complexity: O(1)
*/
static inline void list_push_front(union atomic_data data, struct list *head) {
  list_add(data, head);
  head->data.int_data += 1;
}

static inline int list_size(struct list *head) {
  return head->data.int_data;
}

/**
   @brief Delete @entry by linking the prev and next entries
   @param entry Entry to delete

   Complexity: O(1)
*/
static inline void list_del(struct list *entry) {
  entry->prev->next = entry->next, entry->next->prev = entry->prev;
}

/**
   @brief replace @old entry by @new
   @param old the element to be replaced
   @param new_entry entry to insert

   Complexity: O(1)
 */
static inline void list_replace(struct list *old, struct list *new_entry) {
  new_entry->prev = old->prev;
  new_entry->prev->next = new_entry;
  new_entry->next = old->next;
  new_entry->next->prev = new_entry;
}

/**
   @brief replace head of list from @old to @new_head
   @param old the old head to be deleted
   @param new_head the new head to be inserted

   Complexity: O(1)
*/
static inline void list_replace_head(struct list *old, struct list *new_head) {
  list_replace(old, new_head);
  init_list_head(new_head);
}

/**
   @brief tests whether @entry is the last entry in list
   @param entry entry to test
   @param head the head of the list

   Complexity: O(1)
 */
static inline int list_is_last(const struct list *entry, const struct list *head) {
  return entry->next == head;
}

/**
   @brief tests whether list is empty
   @param head head of list to test

   Complexity: O(1)
 */
static inline int list_empty(const struct list *head) {
  return head->next == head;
}

#define list_for_each(i, pos, head)                                     \
  for (i = 0, pos = (head)->next; pos != (head); pos = pos->next, i++)

/**
   @brief initialize @list with data from @arr
   @param list the list to initialize (should be empty)
   @param arr the array containing initializing data
   @param n size of @arr

   Complexity: (n)
 */
static inline void list_initialize(struct list *list, union atomic_data arr[], int n) {
  assert(n >= 1);
  init_list_head(list);
  for (int i = 0; i < n; i++) {
    list_push_back(arr[i], list);
  }
}

/**
   @brief Deallocate memory inside @head
   @param head list to destroy

   Complexity: O(n)
 */
static inline void list_destroy(struct list *head) {
  assert(!list_empty(head));
  struct list *pos;
  for (pos = head->next; pos != (head);) {
    struct list* next_pos = pos->next;
    free(pos);
    pos = next_pos;
  }
}

/**
   @brief access element at index @idx
   @param head list to search
   @param idx index (0-based)

   Complexity: O(n)
 */
static inline union atomic_data list_at(struct list *head, int idx) {
  struct list *pos = head;
  idx++; // jump from head to real first element
  for (int i = 0; i < idx; i++) {
    pos = pos->next;
  }
  return pos->data;
}

#endif /* _DS_LIB_LIST_H */
