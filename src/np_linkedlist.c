/*
 * np_linkedlist.c: nplib linked list
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

#include <stdlib.h>
#include "np_linkedlist.h"

struct NpLinkedList *np_linkedlist_new()
{
  struct NpLinkedList *list;

  list = malloc(sizeof *list);
  if (list != NULL) {
    list->head = NULL;
  }
  return list;
}

void np_linkedlist_free(struct NpLinkedList *list)
{
  struct NpLinkedListNode *node;
  struct NpLinkedListNode *next;

  node = list->head;
  while (node) {
    next = node->next;
    free(node);
    node = next;
  }
}

void *np_linkedlist_push(struct NpLinkedList *list, void *item)
{
  struct NpLinkedListNode *node;

  node = malloc(sizeof *node);
  if (node == NULL)
    return NULL;
  node->data = item;
  node->next = list->head;
  list->head = node;
  return item;
}

void *np_linkedlist_pop(struct NpLinkedList *list)
{
  struct NpLinkedListNode *node;
  void *item;

  node = list->head;
  if (node == NULL)
    return NULL;
  item = node->data;
  list->head = node->next;
  free(node);
  return item;
}

void np_linkedlist_reverse(struct NpLinkedList *list)
{
  struct NpLinkedListNode *previous;
  struct NpLinkedListNode *next;

  previous = NULL;
  while(list->head) {
    next = list->head->next;
    list->head->next = previous;
    previous = list->head;
    list->head = next;
  }
  list->head = previous;
}

unsigned np_linkedlist_length(struct NpLinkedList *list)
{
  struct NpLinkedListNode *node;
  unsigned length;

  length = 0;
  node = list->head;
  while (node) {
    ++length;
    node = node->next;
  }
  return length;
}

void *np_linkedlist_add(struct NpLinkedList *list, void *item, unsigned index)
{
  struct NpLinkedListNode *node;
  struct NpLinkedListNode *previous;
  struct NpLinkedListNode *current;
  unsigned currentIndex;

  if (index == 0)
    return np_linkedlist_push(list, item);

  currentIndex = 0;
  previous = list->head;
  current = list->head;
  while(previous) {
    if (currentIndex == index) {
      node = malloc(sizeof *node);
      if (node == NULL)
	return NULL;
      node->data = item;
      node->next = current;
      previous->next = node;
      return item;
    }
    currentIndex++;
    previous = current;
    if (current)
      current = current->next;
  }
  return NULL;
}

void *np_linkedlist_remove(struct NpLinkedList *list, unsigned index)
{
  struct NpLinkedListNode *previous;
  struct NpLinkedListNode *current;
  void *item;
  unsigned currentIndex;

  if (index == 0)
    return np_linkedlist_pop(list);

  currentIndex = 0;
  previous = list->head;
  current = list->head;
  while(current) {
    if (currentIndex == index) {
      previous->next = current->next;
      item = current->data;
      free(current);
      return item;
    }
    currentIndex++;
    previous = current;
    current = current->next;
  }
  return NULL;
}
