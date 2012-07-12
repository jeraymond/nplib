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
  struct NpLinkedListNode *prev;
  struct NpLinkedListNode *next;

  prev = NULL;
  while(list->head) {
    next = list->head->next;
    list->head->next = prev;
    prev = list->head;
    list->head = next;
  }
  list->head = prev;
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
