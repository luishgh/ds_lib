#ifndef _DS_LIB_RBT_H
#define _DS_LIB_RBT_H

#include "bst.h"

/**
   Red-Black Tree.

   This is a balanced Bynary Search Tree. This uses the searching facilities of bst.h and modified versions of insertion and deletion to optimize complexities to logarithmic.
 */

enum rbt_color {RED, BLACK};

struct rbt_node {
  struct node node;
  enum rbt_color color;
};

static inline void rbt_initialize(struct rbt_node *root) {
  bst_initialize((struct node *) root);
  root->color = BLACK;
}

static inline void _left_rotate(struct rbt_node *x) {
  struct node *y = x->node.right;

  x->node.right = x->node.left;

  if (y->left != NULL) {
    y->left->parent = &x->node;
  }

  y->parent = x->node.parent;

  if (x->node.parent == &x->node) {
    y->parent = y;
  } else if (&x->node == x->node.parent->left) {
    x->node.parent->left = y;
  } else x->node.parent->right = y;

  y->left = &x->node;
  x->node.parent = y;
}

static inline void _right_rotate(struct rbt_node *y) {
  struct node *x = y->node.left;

  y->node.left = x->right;

  if (x->right != NULL) {
    x->right->parent = &y->node;
  }

  x->parent = y->node.parent;

  if (y->node.parent == &y->node) {
    x->parent = x;
  } else if (&y->node == y->node.parent->right) {
    y->node.parent->right = x;
  } else y->node.parent->left = x;

  x->right = &y->node;
  y->node.parent = x;
}

// fix broken invariants due to insertion
// NOTE: NULL nodes are considered BLACK for all purposes of color checking
static inline void __rbt_fixup(struct rbt_node *root, struct rbt_node *node) {
  struct rbt_node * uncle;
  struct rbt_node * parent = (struct rbt_node*) node->node.parent;
  while (node->node.parent != NULL && parent->color == RED) {
    if (node->node.parent == parent->node.parent->left) {
      uncle = (struct rbt_node*) parent->node.parent->right;

      if (uncle != NULL && uncle->color == RED) {
        parent->color = BLACK;
        uncle->color = BLACK;
        ((struct rbt_node *) parent->node.parent)->color = RED;
        node = (struct rbt_node*) parent->node.parent;
      } else {
        if (&node->node == parent->node.right) {
          node = (struct rbt_node*) node->node.parent;
          _left_rotate(node);
        }

        parent->color = BLACK;
        ((struct rbt_node*) parent->node.parent)->color = BLACK;
        _right_rotate((struct rbt_node*) parent->node.parent);
      }
    } else {
      uncle = (struct rbt_node*) parent->node.parent->left;

      if (uncle != NULL && uncle->color == RED) {
        parent->color = BLACK;
        uncle->color = BLACK;
        ((struct rbt_node*) parent->node.parent)->color = RED;
        node = (struct rbt_node*) parent->node.parent;
      } else {
        if (&node->node == parent->node.left) {
          node = parent;
          _right_rotate(node);
        }

        parent->color = BLACK;
        ((struct rbt_node*) parent->node.parent)->color = RED;
        _left_rotate((struct rbt_node*) parent->node.parent);
      }
    }
  }

  root->color = BLACK;
}

// FIXME: bst_insert mallocs space for bst nodes, not rbt nodes
// use realloc
static inline struct rbt_node* rbt_insert(struct rbt_node *root, union atomic_data data, enum tag type) {
  struct node *node = bst_insert((struct node *) root, data, type);
  struct rbt_node *rbt_node;
  int parent_left = 0;
  if (root->node.size != 1) {
    if (node == node->parent->left) parent_left = 1;
    rbt_node = (struct rbt_node*) realloc(node, sizeof(struct rbt_node));
    rbt_node->color = RED;
    if (parent_left) rbt_node->node.parent->left = (struct node*) rbt_node;
    else rbt_node->node.parent->right = (struct node*) rbt_node;
    __rbt_fixup(root, rbt_node);
  } else rbt_node = (struct rbt_node *) node;
  return rbt_node;
}

#endif /* _DS_LIB_RBT_H */
