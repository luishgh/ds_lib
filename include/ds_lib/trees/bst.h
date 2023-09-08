#ifndef _DS_LIB_BST_H
#define _DS_LIB_BST_H

// Author: Luis Henrique Gomes Higino

#include <stdlib.h>
#include <assert.h>

#include "../types.h"

/**
   Simple Binary Search Tree.

   This BST doesn't have balancing, so it can degenerate to a line. This means operations are worst-case linear, instead of logarithmic as we would hope.

   Complexities:
   bst_search: O(n)
   bst_insert: O(n)
*/

struct node {
  struct tagged_atomic data;
  struct node* left;
  struct node* right;
  struct node* parent;
  size_t size;
};

//! initialize bst root
static inline void bst_initialize(struct node *root) {
  root->left = NULL, root->right = NULL;
  root->parent = root;
  root->size = 0;
}

static inline void __bst_insert_leaf(struct node **node, struct node *parent, struct tagged_atomic data) {
  *node = (struct node*) malloc(sizeof (struct node));
  (*node)->data = data;
  (*node)->parent = parent;
  (*node)->left = NULL;
  (*node)->right = NULL;
}

static inline void __bst_insert_int(struct node *node, struct tagged_atomic data) {
  assert(data.tag == INT);
  if (data.data.int_data <= node->data.data.int_data) {
    if (node->left == NULL) __bst_insert_leaf(&node->left, node, data);
    else __bst_insert_int(node->left, data);
  } else {
    if (node->right == NULL) __bst_insert_leaf(&node->right, node, data);
    else __bst_insert_int(node->right, data);
  }
}

static inline void __bst_insert(struct node *root, struct tagged_atomic data) {
  // fill root
  if (root->size == 0) {
    root->data = data;
    return;
  }
  // FIXME: add other types
  switch(data.tag) {
  case(INT):
    __bst_insert_int(root, data);
    break;
  }
}

/**
   @brief insert @data into tree
   @param root root of the tree
   @param data data to be inserted

   Complexity: O(n)
 */
static inline void bst_insert(struct node *root, union atomic_data data, enum tag type) {
  struct tagged_atomic ta = {data, type};
  __bst_insert(root, ta);
  root->size++;
}

static inline int __bst_search_int(struct node *node, struct tagged_atomic data) {
  assert(data.tag == INT);

  if(node == NULL) return 0;

  int node_val = node->data.data.int_data;
  int search_val = data.data.int_data;

  if (node_val == search_val) return 1;

  if (search_val < node_val) return __bst_search_int(node->left, data);
  else return __bst_search_int(node->right, data);
}

static inline int __bst_search(struct node *root, struct tagged_atomic data) {
  // FIXME: add other types
  switch(data.tag) {
  case(INT):
    return __bst_search_int(root, data);
  }
}

/**
   @brief search @data inside tree
   @param root root of the tree
   @param data data to be searched

   Complexity: O(n)
 */
static inline int bst_search(struct node *root, union atomic_data data, enum tag type) {
  struct tagged_atomic ta = {data, type};
  return __bst_search(root, ta);
}

/**
   @brief get minimum element inside tree
   @param root root of the tree

   Complexity: O(n)
*/
static union atomic_data bst_min(struct node *root) {
  while (root->left != NULL) {
    root = root->left;
  }

  return root->data.data;
}

/**
   @brief get maximum element inside tree
   @param root root of the tree

   Complexity: O(n)
*/
static union atomic_data bst_max(struct node *root) {
  while (root->right != NULL) {
    root = root->right;
  }

  return root->data.data;
}

#endif /* _DS_LIB_BST_H */
