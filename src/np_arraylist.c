/*
 * np_arraylist.c: nplib array list
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
#include <limits.h>

#include "np_arraylist.h"

struct NpArrayList *np_arraylist_new()
{
  struct NpArrayList *list;

  list = malloc(sizeof *list);
  if (list == NULL)
    return NULL;
  list->size = 0;
  list->allocated = NP_ARRAYLIST_DEFAULT_ALLOC_SIZE;
  list->data = malloc((sizeof *list->data) * NP_ARRAYLIST_DEFAULT_ALLOC_SIZE);
  if (list->data == NULL) {
    free(list);
    return NULL;
  }
  return list;
}

void np_arraylist_free(struct NpArrayList *list)
{
  free(list->data);
  free(list);
}

static struct NpArrayList *np_arraylist_realloc(struct NpArrayList *list)
{
  int allocated;
  void *data;

  if (list->size  == list->allocated) {
    allocated = list->allocated;

    /* Double the allocation if possible, otherwise set to MAX_INT */
    if (allocated == INT_MAX)
      return NULL;
    if (allocated > INT_MAX >> 1) /* check for overflow */
      allocated = INT_MAX;
    else
      allocated = allocated << 1;
    data = realloc(list->data, (sizeof *list->data) * allocated);
    if (data == NULL)
      return NULL;
    list->data = data;
    list->allocated = allocated;
  }
  return list;
}

void *np_arraylist_push(struct NpArrayList *list, void *item)
{
  int i;

  list = np_arraylist_realloc(list);
  if (list == NULL)
    return NULL;
  for (i = list->size; i > 0; --i)
    list->data[i] = list->data[i - 1];
  list->data[0] = item;
  list->size++;
  return item;
}

void *np_arraylist_pop(struct NpArrayList *list)
{
  int i;
  int size;
  void *item;

  if (list->size == 0)
    return NULL;
  item = list->data[0];
  size = list->size - 1;
  for (i = 0; i < size; ++i)
    list->data[i] = list->data[i + 1];
  list->size--;
  return item;
}

void np_arraylist_reverse(struct NpArrayList *list)
{
  void *temp;
  int i;
  int j;

  j = list->size - 1;
  i = 0;
  while (i < j) {
    temp = list->data[i];
    list->data[i] = list->data[j];
    list->data[j] = temp;
    ++i;
    --j;
  }
}

int np_arraylist_length(struct NpArrayList *list)
{
  return list->size;
}

void *np_arraylist_add(struct NpArrayList *list, void *item, int index)
{
  int i;

  list = np_arraylist_realloc(list);
  if (list == NULL)
    return NULL;
  if (index < 0 || index > list->size)
    return NULL;
  for (i = list->size; i > index; --i)
    list->data[i] = list->data[i - 1];
  list->data[index] = item;
  list->size++;
  return item;
}

void *np_arraylist_remove(struct NpArrayList *list, int index)
{
  int i;
  int size;
  void *item;

  if (index < 0 || index > list->size - 1)
    return NULL;
  size = list->size;
  item = list->data[index];
  for (i = index; i < list->size; ++i)
    list->data[i] = list->data[i + 1];
  list->size--;
  return item;
}

void *np_arraylist_get(struct NpArrayList *list, int index)
{
  if (index < 0 || index > list->size -1)
    return NULL;
  return list->data[index];
}

struct NpArrayListIterator *np_arraylist_iterator(struct NpArrayList *list)
{
  struct NpArrayListIterator *iter;

  iter = malloc(sizeof *iter);
  if (iter == NULL)
    return NULL;
  iter->list = list;
  iter->index = 0;
  return iter;
}

void np_arraylist_iterator_free(struct NpArrayListIterator *iter)
{
  free(iter);
}

void *np_arraylist_iterator_next(struct NpArrayListIterator *iter)
{
  void *item;
  if (iter->index < iter->list->size) {
    item = iter->list->data[iter->index];
    iter->index++;
    return item;
  }
  return NULL;
}
