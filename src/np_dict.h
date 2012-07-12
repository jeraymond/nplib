/*
 * np_dict.h: nplib dictionary header file
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

#ifndef __NP_DICT_H
#define __NP_DICT_H

#define DICT_SIZE 256

/**
   Dictionary object
*/
struct NpDict {

  /**
     Pointer to a function used to compare dictionary keys.

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
     The number of items in the dictionary
  */
  unsigned size;

  /**
     A Pointer to the items
  */
  struct NpDictItem **items;
};

/**
   Dictionary item
*/
struct NpDictItem {
  /**
     The item key.
  */
  void *key;

  /**
     The item value.
  */
  void *value;

  /**
     The next item
  */
  struct NpDictItem *next;
};

/**
   Allocates memory for and initializes a dictionary.

   @param key_compare The function to be used for comparing keys.
   @param key_hash The function to be used for hashing keys.
   @return a pointer to the allocated memory or NULL on error.
*/
struct NpDict *np_dict_new(int (*cmp)(void *key1, void *key2),
                            unsigned (*hash)(void *key));

/**
   Frees the memory used by the dictionary. Does _not_ free the keys or values.

   @param dict The dictionary to free.
*/
void np_dict_free(struct NpDict *dict);

/**
   Puts an item into the dictionary.

   @param dict The dictionary in which to put the item.
   @param key The at which to store the value, replacing an existing item.
   @param value The value to store.
   @return a pointer to the added item or NULL on error.
*/
void *np_dict_put(struct NpDict *dict, void *key, void *value);

/**
   Gets an item from the dictionary.

   @param dict The dictionary from which to retrieve the item.
   @param key The key of the item to retrieve.
   @return a pointer to the item or NULL on error or if the item does not exist.
*/
void *np_dict_get(struct NpDict *dict, void *key);


/**
   Removes and item from the dictionary.

   @param dict The dict from which to remove the item.
   @param key The key of the item to remove.
   @return a pointer to the removed item or NULL on error or if there is no item
   at the given key.
*/
void *np_dict_remove(struct NpDict *dict, void *key);

/**
   Creates a hash for the key of the given length.

   @param key The key to hash.
   @param length The length of the key.
   @return the hash.
*/
unsigned np_dict_hash(void *key, int length);

#endif
