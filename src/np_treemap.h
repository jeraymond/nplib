/*
 * np_treemap.h: nplib tree map header file
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

#ifndef __NP_TREEMAP_H
#define __NP_TREEMAP_H

/**
   Tree node colors.
*/
enum NpTreeMapColor {
  RED,
  BLACK
};

/**
   Tree map node.
*/
struct NpTreeMapNode {
  /**
     The map key.
  */
  void *key;

  /**
     The map value.
  */
  void *value;

  /**
     The map red/black tree color.
  */
  enum NpTreeMapColor color;

  /**
     The node parent.
  */
  struct NpTreeMapNode *parent;

  /**
     The node's left child.
  */
  struct NpTreeMapNode *left;

  /**
     The nodes right child.
  */
  struct NpTreeMapNode *right;
};

/**
   Tree map object.
*/
struct NpTreeMap {
  /**
     Sentinel root node.
  */
  struct NpTreeMapNode root;

  /**
     The null node. Represents a non-existent item and leaves. Used to simplify
     algorithm logic.
  */
  struct NpTreeMapNode nil;

  /**
     A comparator function for the map keys.
  */
  int (*comparator)(void *key1, void *key2);
};

/**
   Tree map iterator.
*/
struct NpTreeMapIterator {
  /**
     The map being iterated over.
  */
  struct NpTreeMap *map;

  /**
     The next node.
  */
  struct NpTreeMapNode *node;
};

/**
   Allocates memory for and initializes a tree map.

   @param comparator the key comparator function
   @return a pointer to the allocated memory or NULL on error
*/
struct NpTreeMap *np_treemap_new(int (*comparator)(void *key1, void *key2));

/**
   Frees the memory used by the map. Does not free the keys or values contained
   in the map.
*/
void np_treemap_free(struct NpTreeMap *map);

/**
   Puts a item into the map.

   @param map the map
   @param key the key used to store/retrieve the value
   @param value the value
   @return a pointer to the added item or NULL on error
*/
void *np_treemap_put(struct NpTreeMap *map, void *key, void *value);

/**
   Gets an item from the map.

   @param map the map
   @param key the search key
   @return a pointer to the item or NULL if the item is not found
*/
void *np_treemap_get(struct NpTreeMap *map, void *key);

/**
   Removes an item from the map.

   @param map the map
   @param key the search key
   @return the removed item or NULL if the item is not found
*/
void *np_treemap_remove(struct NpTreeMap *map, void *key);

/**
   Creates a key iterator for the map. The map must not be modified while
   using the iterator. If the map is modified the iterator behaviour is
   undefined.

   @param map the map
   @return the key iterator
*/
struct NpTreeMapIterator *np_treemap_iterator(struct NpTreeMap *map);

/**
   Frees the memory used by the iterator.

   @param iter the iterator to free
*/
void np_treemap_iterator_free(struct NpTreeMapIterator *iter);

/**
   Retrieves the next key from the iterator.

   @param iter the iterator
   @return the next key in the map or NULL if no keys are left
*/
void *np_treemap_iterator_next_key(struct NpTreeMapIterator *iter);

/**
   Retrieves the next key without advancing the iterator.

   @param iter the iterator
   @return the next key or NULL if no keys are left
*/
void *np_treemap_iterator_peek_next_key(struct NpTreeMapIterator *iter);

/**
   Retrieves the next value without advancing the iterator.

   @param iter the iterator
   @return the next value or NULL if no values are left
*/
void *np_treemap_iterator_peek_next_value(struct NpTreeMapIterator *iter);

#endif
