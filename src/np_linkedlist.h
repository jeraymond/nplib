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

struct NpLinkedList {
  struct NpLinkedListNode *head;
};

struct NpLinkedListNode {
  void *data;
  struct NpLinkedListNode *next;
};

struct NpLinkedList *np_linkedlist_new();
void np_linkedlist_free(struct NpLinkedList *list);
void *np_linkedlist_push(struct NpLinkedList *list, void *item);
void *np_linkedlist_pop(struct NpLinkedList *list);
void np_linkedlist_reverse(struct NpLinkedList *list);
unsigned np_linkedlist_length(struct NpLinkedList *list);

#endif
