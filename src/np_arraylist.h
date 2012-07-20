/*
 * np_arraylist.h: nplib array list header file
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

#ifndef __NP_ARRAYLIST_H
#define __NP_ARRAYLIST_H

#define NP_ARRAYLIST_DEFAULT_ALLOC_SIZE 10

/**
   Array list object.
*/
struct NpArrayList {
  /**
     Number of slots allocated in the list.
  */
  int allocated;

  /**
     The current size of the list.
  */
  int size;

  /**
     Pointer to the list data.
  */
  void **data;
};

/**
   Array list iterator.
*/
struct NpArrayListIterator {
  /**
     Pointer to the list.
  */
  struct NpArrayList *list;

  /**
     The current index.
  */
  int index;
};

/**
   Allocates memory for and initializes an array list.
*/
struct NpArrayList *np_arraylist_new();

/**
   Frees the memory used by the list. Does not free the values contained in the
   list.

   @param list the list to free
*/
void np_arraylist_free(struct NpArrayList *list);

/**
   Adds an item to the head of the list.

   @param list the list
   @param item the item to push
   @return the pushed item or NULL on error
*/
void *np_arraylist_push(struct NpArrayList *list, void *item);

/**
   Removes the item at the head of the list.

   @param list the list
   @return the first item in the list or NULL on error
*/
void *np_arraylist_pop(struct NpArrayList *list);

/**
   Reverses the list.

   @param list the list
*/
void np_arraylist_reverse(struct NpArrayList *list);

/**
   Determines the length of the list.

   @param list the list
   @return the length of the list
*/
int np_arraylist_length(struct NpArrayList *list);

/**
   Adds the item to the list at the given index shifting the existing item at
   the index (if any) and subsequent items to the right.

   @param list the list
   @param item the item to add
   @param index the insert index
   @return the added item or NULL on error
*/
void *np_arraylist_add(struct NpArrayList *list, void *item, int index);

/**
   Removes the item at the given index shifting any remaining items after
   that index (if any) to the left.

   @param list the list
   @param index the removal index
   @return the item removed or NULL on error
*/
void *np_arraylist_remove(struct NpArrayList *list, int index);

/**
   Gets the item at the given index.

   @param list the list
   @param index the index of the item to get
   @return the item at the index or NULL if there is no such item
*/
void *np_arraylist_get(struct NpArrayList *list, int index);

/**
   Creates a new iterator for the given list. Free the iterator with
   np_arraylist_iterator_free() when done with it.

   @param list the list
   @return the iterator or NULL if the iterator could not be created
*/
struct NpArrayListIterator *np_arraylist_iterator(struct NpArrayList *list);

/**
   Frees the memory used by the iterator.

   @param iter the iterator
*/
void np_arraylist_iterator_free(struct NpArrayListIterator *iter);

/**
   Gets the next item from the iterator.

   @param iter the iterator
   @return the next item or NULL when no items are left
*/
void *np_arraylist_iterator_next(struct NpArrayListIterator *iter);

#endif

