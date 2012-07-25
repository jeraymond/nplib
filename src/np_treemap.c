/*
 * np_treemap.c: nplib tree map
 *
 * Copyright 2012 Jeremy Raymond
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Adapted from http://opensource.apple.com/source/sudo/sudo-46/src/redblack.c
 *
 * Copyright (c) 2004-2005, 2007 Todd C. Miller <Todd.Miller@courtesan.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdlib.h>

#include "np_treemap.h"

struct NpTreeMap *np_treemap_new(int (*comparator)(void *key1, void *key2))
{
  struct NpTreeMap *map;

  map = malloc(sizeof *map);
  if (map) {
    map->comparator = comparator;

    /*
     * Use self referencing sentinel node named nil to simplify code by
     * avoiding need to check for NULL pointers.
     */
    map->nil.left = map->nil.right = map->nil.parent = &map->nil;
    map->nil.color = BLACK;
    map->nil.key = NULL;
    map->nil.value = NULL;

    /*
     * The sentinel root node, root->left always points to the true
     * root item of the tree.
     */
    map->root.left = map->root.right = map->root.parent = &map->nil;
    map->root.color = BLACK;
    map->root.key = NULL;
    map->root.value = NULL;
  }
  return map;
}

static void np_treemap_rotate_left(struct NpTreeMap *map,
				   struct NpTreeMapNode *node)
{
  struct NpTreeMapNode *child;

  child = node->right;
  node->right = child->left;

  if (child->left != &map->nil)
    child->left->parent = node;
  child->parent = node->parent;

  if (node == node->parent->left)
    node->parent->left = child;
  else
    node->parent->right = child;
  child->left = node;
  node->parent = child;
}

static void np_treemap_rotate_right(struct NpTreeMap *map,
				    struct NpTreeMapNode *node)
{
  struct NpTreeMapNode *child;

  child = node->left;
  node->left = child->right;

  if (child->right != &map->nil)
    child->right->parent = node;
  child->parent = node->parent;

  if (node == node->parent->left)
    node->parent->left = child;
  else
    node->parent->right = child;
  child->right = node;
  node->parent = child;
}

void np_treemap_free(struct NpTreeMap *map)
{
  struct NpTreeMapNode *node;
  struct NpTreeMapNode *parent;

  node = map->root.left;
  while (node != &map->nil) {
    if (node->left != &map->nil) {
      node = node->left;
    } else if (node->right != &map->nil) {
      node = node->right;
    } else {
      parent = node->parent;
      if (parent->left == node)
	parent->left = &map->nil;
      else
	parent->right = &map->nil;
      if (node != &map->root)
	free(node);
      node = parent;
    }
  }
  free(map);
}

void *np_treemap_put(struct NpTreeMap *map, void *key, void *value)
{
  struct NpTreeMapNode *node;
  struct NpTreeMapNode *parent;
  int cmp;

  /* binary insertion of node */
  node = map->root.left;
  parent = &map->root;
  while (node != &map->nil) {
    parent = node;

    /* replace existing item value */
    if ((cmp = map->comparator(key, node->key)) == 0) {
      node->value = value;
      return value;
    }
    node = cmp < 0 ? node->left : node->right;
  }

  node = malloc(sizeof *node);
  if (node == NULL)
    return NULL;
  node->key = key;
  node->value = value;
  node->parent = parent;
  node->left = node->right = &map->nil;
  if (parent == &map->root || map->comparator(key, parent->key) < 0)
    parent->left = node;
  else
    parent->right = node;
  node->color = RED;

  /*
   * If parent node is black no further changes are needed. Otherwise we
   * need to ensure tree maintains red/black tree properties.
   */
  while(node->parent->color == RED) {
    struct NpTreeMapNode *uncle;

    if (node->parent == node->parent->parent->left) {
      uncle = node->parent->parent->right;
      if (uncle->color == RED) {
	node->parent->color = BLACK;
	uncle->color = BLACK;
	node->parent->parent->color = RED;
	node = node->parent->parent;
      } else {
	if (node == node->parent->right) {
	  node = node->parent;
	  np_treemap_rotate_left(map, node);
	}
	node->parent->color = BLACK;
	node->parent->parent->color = RED;
	np_treemap_rotate_right(map, node->parent->parent);
      }
    } else {
      uncle = node->parent->parent->left;
      if (uncle->color == RED) {
	node->parent->color = BLACK;
	uncle->color = BLACK;
	node->parent->parent->color = RED;
	node = node->parent->parent;
      } else {
	if (node == node->parent->left) {
	  node = node->parent;
	  np_treemap_rotate_right(map, node);
	}
	node->parent->color = BLACK;
	node->parent->parent->color = RED;
	np_treemap_rotate_left(map, node->parent->parent);
      }
    }
  }
  map->root.left->color = BLACK; /* first node is always black */
  return value;
}

void *np_treemap_get(struct NpTreeMap *map, void *key)
{
  struct NpTreeMapNode *node;
  int cmp;

  node = map->root.left;
  while (node != &map->nil) {
    if ((cmp = map->comparator(key, node->key)) == 0)
      return node->value;
    node = cmp < 0 ? node->left : node->right;
  }
  return NULL;
}

static struct NpTreeMapNode *np_treemap_successor(struct NpTreeMap *map,
						  struct NpTreeMapNode *node)
{
  struct NpTreeMapNode *successor;

  if ((successor = node->right) != &map->nil) {
    while (successor->left != &map->nil)
      successor = successor->left;
  } else {
    for (successor = node->parent; node == successor->right;
	 successor = successor->parent)
      node = successor;
    if (successor == &map->root)
      successor = &map->nil;
  }
  return successor;
}

static void np_treemap_repair(struct NpTreeMap *map,
			      struct NpTreeMapNode *node)
{
  struct NpTreeMapNode *sibling;

  while (node->color == BLACK) {
    if (node == node->parent->left) {
      sibling = node->parent->right;
      if (sibling->color == RED) {
	sibling->color = BLACK;
	node->parent->color = RED;
	np_treemap_rotate_left(map, node->parent);
	sibling = node->parent->right;
      }
      if (sibling->right->color == BLACK && sibling->left->color == BLACK) {
	sibling->color = RED;
	node = node->parent;
      } else {
	if (sibling->right->color == BLACK) {
	  sibling->left->color = BLACK;
	  sibling->color = RED;
	  np_treemap_rotate_right(map, sibling);
	}
	sibling->color = node->parent->color;
	node->parent->color = BLACK;
	sibling->right->color = BLACK;
	np_treemap_rotate_left(map, node->parent);
	break;
      }
    } else {
      sibling = node->parent->left;
      if (sibling->color == RED) {
	sibling->color = BLACK;
	node->parent->color = RED;
	np_treemap_rotate_right(map, node->parent);
	sibling = node->parent->left;
      }
      if (sibling->right->color == BLACK && sibling->left->color == BLACK) {
	sibling->color = RED;
	node = node->parent->left;
      } else {
	if (sibling->left->color == BLACK) {
	  sibling->right->color = BLACK;
	  sibling->color = RED;
	  np_treemap_rotate_left(map, sibling);
	  sibling = node->parent->left;
	}
	sibling->color = node->parent->color;
	node->parent->color = BLACK;
	sibling->left->color = BLACK;
	np_treemap_rotate_right(map, node->parent);
	break;
      }
    }
  }
}

void *np_treemap_remove(struct NpTreeMap *map, void *key)
{
  struct NpTreeMapNode *x;
  struct NpTreeMapNode *y;
  struct NpTreeMapNode *node;
  int cmp;
  void *value;

  node = map->root.left;
  while (node != &map->nil) {
    if ((cmp = map->comparator(key, node->key)) == 0)
      break;
    node = cmp < 0 ? node->left : node->right;
  }
  if (node == &map->nil)
    return NULL; /* did not find node to remove */

  value = node->value;
  if (node->left == &map->nil || node->right == &map->nil)
    y = node;
  else
    y = np_treemap_successor(map, node);
  x = y->left == &map->nil ? y->right : y->left;

  if ((x->parent = y->parent) == &map->root) {
    map->root.left = x;
  } else {
    if (y == y->parent->left)
      y->parent->left = x;
    else
      y->parent->right = x;
  }
  if (y->color == BLACK)
    np_treemap_repair(map, x);
  if (y != node) {
    y->left = node->left;
    y->right = node->right;
    y->parent = node->parent;
    y->color = node->color;
    node->left->parent = node->right->parent = y;
    if (node == node->parent->left)
      node->parent->left = y;
    else
      node->parent->right = y;
  }
  free(node);
  return value;
}

struct NpTreeMapIterator *np_treemap_iterator(struct NpTreeMap *map)
{
  struct NpTreeMapIterator *iter;
  struct NpTreeMapNode *node;

  iter = malloc(sizeof *iter);
  if (iter) {
    iter->map = map;

    /* initialize first node to be left most node */
    node = map->root.left;
    while(node->left != &map->nil)
      node = node->left;
    iter->node = node;
  }
  return iter;
}

void np_treemap_iterator_free(struct NpTreeMapIterator *iter)
{
  free(iter);
}

void *np_treemap_iterator_next_key(struct NpTreeMapIterator *iter)
{
  struct NpTreeMapNode *node;
  void *key;

  key = NULL;
  node = iter->node;
  if (node != &iter->map->nil) {
    key = node->key;
  }
  if (node->right != &iter->map->nil) {
    node = node->right;
    while (node->left != &iter->map->nil)
      node = node->left;
  } else {
    while (node->parent != &iter->map->nil && node == node->parent->right)
      node = node->parent;
    node = node->parent;
  }
  iter->node = node;
  return key;
}

void *np_treemap_iterator_peek_next_key(struct NpTreeMapIterator *iter)
{
  struct NpTreeMapNode *node;

  node = iter->node;
  if (node != &iter->map->nil)
    return node->key;
  else
    return NULL;
}

void *np_treemap_iterator_peek_next_value(struct NpTreeMapIterator *iter)
{
  struct NpTreeMapNode *node;

  node = iter->node;
  if (node != &iter->map->nil)
    return node->value;
  else
    return NULL;
}
