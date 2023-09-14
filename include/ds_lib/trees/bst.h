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

// NOTE: Using node->size to determine when the tree is empty is kinda bad, as we add a size_t into every single node and it contains garbage for all but the root node. I will try to improve this in the future, but I really don't want a wrapper struct with a pointer to the root node :/.

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

static inline struct node* __bst_insert(struct node *root, struct tagged_atomic data) {
  // fill root
  if (root->size == 0) {
    root->data = data;
    return root;
  }
  struct node *node = root;
  while (1) {
    if (compare_atomic(data, node->data)) {
      if (node->left == NULL) {
        __bst_insert_leaf(&node->left, node, data);
        return node->left;
      }
      else node = node->left;
    } else {
      if (node->right == NULL) {
        __bst_insert_leaf(&node->right, node, data);
        return node->right;
      }
      else node = node->right;
    }
  }
}

/**
   @brief insert @data into tree
   @param root root of the tree
   @param data data to be inserted

   Complexity: O(n)
 */
static inline struct node* bst_insert(struct node *root, union atomic_data data, enum tag type) {
  struct tagged_atomic ta = {data, type};
  struct node* ret = __bst_insert(root, ta);
  root->size++;
  return ret;
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
