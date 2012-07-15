/*
 * np_linkedlist.h: nplib linked list header file
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

#ifndef __NP_LINKEDLIST_H
#define __NP_LINKEDLIST_H

/**
   Linked list object
*/
struct NpLinkedList {

  /**
     The head of the list
  */
  struct NpLinkedListNode *head;
};

/**
   Linked list node
*/
struct NpLinkedListNode {

  /**
     Pointer to the node data
  */
  void *data;

  /**
     The next node in the list
  */
  struct NpLinkedListNode *next;
};

/**
   Allocates memory for and initializes a linked list.

   @return a pointer to the allocated memory or NULL on error
*/
struct NpLinkedList *np_linkedlist_new();

/**
   Frees the memory used by the list. Does not free the values contained in the
   list.

   @param list the list to free
*/
void np_linkedlist_free(struct NpLinkedList *list);

/**
   Adds an item to the head of the list.

   @param list the list
   @param item the item to push
   @return the pushed item or NULL on error
*/
void *np_linkedlist_push(struct NpLinkedList *list, void *item);

/**
   Removes the item at the head of the list.

   @param list the list
   @return the first item in the list or NULL on error
*/
void *np_linkedlist_pop(struct NpLinkedList *list);

/**
   Reverses the list.

   @param list the list
*/
void np_linkedlist_reverse(struct NpLinkedList *list);

/**
   Determines the length of the list.

   @param list the list
   @return the length of the list
*/
unsigned np_linkedlist_length(struct NpLinkedList *list);

/**
   Adds the item to the list at the given index shifting the existing item at
   the index (if any) and subsequent items to the right.

   @param list the list
   @param item the item to add
   @param index the insert index
   @return the added item or NULL on error
*/
void *np_linkedlist_add(struct NpLinkedList *list, void *item, unsigned index);

/**
   Removes the item at the given index shifting any remaining items after
   that index (if any) to the left.

   @param list the list
   @param index the removal index
   @return the item removed or NULL on error
*/
void *np_linkedlist_remove(struct NpLinkedList *list, unsigned index);

#endif
