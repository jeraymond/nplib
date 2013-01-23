/*
 * np_hashmap.h: nplib hash map header file
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

#ifndef __NP_HASHMAP_H
#define __NP_HASHMAP_H

#define NP_HASHMAP_INITIAL_CAPACITY 16
#define NP_HASHMAP_DEFAULT_LOAD_FACTOR 0.75

/**
   Hash map object.
*/
struct NpHashMap {

  /**
     Pointer to a function used to compare map keys.

     @param key1 the first key
     @param key2 the second key
     @return 0 if keys are equal, value > 0 if first key is greater than
     the second key, value < 0 if the first key is lesser than the second
  */
  int (*key_compare)(void *key1, void *key2);

  /**
     Pointer to a function used to hash keys.

     @param key the key to hash
     @return the hash
  */
  unsigned (*key_hash)(void *key);

  /**
     The map capacity.
  */
  unsigned capacity;

  /**
     The number of items in the map.
  */
  unsigned size;

  /**
     The next size at which the map will grow (capacity * load_factor).
   */
  unsigned threshold;

  /**
     The load factor.
  */
  float load_factor;

  /**
     A Pointer to the items.
  */
  struct NpHashMapItem **items;
};

/**
   Hash map item.
*/
struct NpHashMapItem {
  /**
     The item key.
  */
  void *key;

  /**
     The item value.
  */
  void *value;

  /**
     The next item.
  */
  struct NpHashMapItem *next;
};

/**
   Allocates memory for and initializes a map.

   @param key_compare the function to be used for comparing keys
   @param key_hash the function to be used for hashing keys
   @return a pointer to the allocated memory or NULL on error
*/
struct NpHashMap *np_hashmap_new(int (*cmp)(void *key1, void *key2),
                            unsigned (*hash)(void *key));

/**
   Frees the memory used by the map. Does not free the keys or values.

   @param map the map to free
*/
void np_hashmap_free(struct NpHashMap *map);

/**
   Puts an item into the map.

   @param map the map in which to put the item
   @param key the key at which to store the value, replacing an existing item
   @param value the value to store
   @return a pointer to the added item or NULL on error
*/
void *np_hashmap_put(struct NpHashMap *map, void *key, void *value);

/**
   Gets an item from the map.

   @param map the map from which to retrieve the item
   @param key the key of the item to retrieve
   @return a pointer to the item or NULL on error or if the item does not exist
*/
void *np_hashmap_get(struct NpHashMap *map, void *key);


/**
   Removes and item from the map.

   @param map the map from which to remove the item.
   @param key the key of the item to remove
   @return a pointer to the removed item or NULL on error or if there is no item
   at the given key.
*/
void *np_hashmap_remove(struct NpHashMap *map, void *key);

/**
   Creates a hash for the key of the given length.

   @param key the key to hash
   @param length the length of the key
   @return the hash
*/
unsigned np_hashmap_hash(void *key, int length);

#endif
