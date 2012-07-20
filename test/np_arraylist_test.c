/*
 * np_arraylist_test.c: nplib array list tests
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

#include <CUnit/Basic.h>
#include <string.h>

#include "np_arraylist_test.h"
#include "np_arraylist.h"

void np_arraylist_test_basics(void) {
  struct NpArrayList *list;
  char *data1 = "The first data item";
  char *data2 = "The second data item";
  char *data3 = "The thrid data item";

  /* push and pop */
  CU_ASSERT_NOT_EQUAL(NULL, list = np_arraylist_new());
  CU_ASSERT_EQUAL(data1, np_arraylist_push(list, data1));
  CU_ASSERT_EQUAL(data1, np_arraylist_pop(list));
  CU_ASSERT_EQUAL(NULL, np_arraylist_pop(list));
  CU_ASSERT_EQUAL(data1, np_arraylist_push(list, data1));
  CU_ASSERT_EQUAL(data2, np_arraylist_push(list, data2));
  CU_ASSERT_EQUAL(data2, np_arraylist_pop(list));
  CU_ASSERT_EQUAL(data1, np_arraylist_pop(list));
  CU_ASSERT_EQUAL(NULL, np_arraylist_pop(list));

  /* reverse */
  np_arraylist_reverse(list);
  CU_ASSERT_EQUAL(NULL, np_arraylist_pop(list));

  np_arraylist_push(list, data1);
  np_arraylist_reverse(list);
  CU_ASSERT_EQUAL(data1, np_arraylist_pop(list));
  CU_ASSERT_EQUAL(NULL, np_arraylist_pop(list));

  np_arraylist_push(list, data1);
  np_arraylist_push(list, data2);
  np_arraylist_reverse(list);
  CU_ASSERT_EQUAL(data1, np_arraylist_pop(list));
  CU_ASSERT_EQUAL(data2, np_arraylist_pop(list));
  CU_ASSERT_EQUAL(NULL, np_arraylist_pop(list));

  np_arraylist_push(list, data1);
  np_arraylist_push(list, data2);
  np_arraylist_push(list, data3);
  np_arraylist_reverse(list);
  CU_ASSERT_EQUAL(data1, np_arraylist_pop(list));
  CU_ASSERT_EQUAL(data2, np_arraylist_pop(list));
  CU_ASSERT_EQUAL(data3, np_arraylist_pop(list));
  CU_ASSERT_EQUAL(NULL, np_arraylist_pop(list));

  /* length */
  CU_ASSERT_EQUAL(0, np_arraylist_length(list));
  np_arraylist_push(list, data1);
  CU_ASSERT_EQUAL(1, np_arraylist_length(list));
  np_arraylist_push(list, data1);
  CU_ASSERT_EQUAL(2, np_arraylist_length(list));

  np_arraylist_free(list);
}

void np_arraylist_test_add(void)
{
  struct NpArrayList *list;
  char *data1 = "The first data item";
  char *data2 = "The second data item";
  char *data3 = "The third data item";

  list = np_arraylist_new();

  /* insert past end of list */
  CU_ASSERT_EQUAL(NULL, np_arraylist_add(list, data1, 1));
  CU_ASSERT_EQUAL(NULL, np_arraylist_add(list, data1, 2));

  /* insert at head of list */
  CU_ASSERT_EQUAL(data1, np_arraylist_add(list, data1, 0));
  CU_ASSERT_EQUAL(1, np_arraylist_length(list));

  /* insert at tail of list */
  CU_ASSERT_EQUAL(data2, np_arraylist_add(list, data2, 1));
  CU_ASSERT_EQUAL(2, np_arraylist_length(list));

  /* insert in middle of list */
  CU_ASSERT_EQUAL(data3, np_arraylist_add(list, data3, 1));
  CU_ASSERT_EQUAL(3, np_arraylist_length(list));

  /* verify item order */
  CU_ASSERT_EQUAL(data1, np_arraylist_pop(list));
  CU_ASSERT_EQUAL(data3, np_arraylist_pop(list));
  CU_ASSERT_EQUAL(data2, np_arraylist_pop(list));
  CU_ASSERT_EQUAL(0, np_arraylist_length(list));

  np_arraylist_free(list);
}

void np_arraylist_test_remove(void)
{
  struct NpArrayList *list;
  char *data1 = "The first data item";
  char *data2 = "The second data item";
  char *data3 = "The third data item";

  list = np_arraylist_new();

  /* remove item from empty list */
  CU_ASSERT_EQUAL(NULL, np_arraylist_remove(list, 0));
  CU_ASSERT_EQUAL(NULL, np_arraylist_remove(list, 1));

  /* remove item at head of list */
  CU_ASSERT_EQUAL(data1, np_arraylist_add(list, data1, 0));
  CU_ASSERT_EQUAL(1, np_arraylist_length(list));
  CU_ASSERT_EQUAL(data1, np_arraylist_remove(list, 0));
  CU_ASSERT_EQUAL(0, np_arraylist_length(list));

  /* remove item at end of list */
  CU_ASSERT_EQUAL(data1, np_arraylist_push(list, data1));
  CU_ASSERT_EQUAL(data2, np_arraylist_push(list, data2));
  CU_ASSERT_EQUAL(2, np_arraylist_length(list));
  CU_ASSERT_EQUAL(data1, np_arraylist_remove(list, 1));
  CU_ASSERT_EQUAL(1, np_arraylist_length(list));
  CU_ASSERT_EQUAL(data2, np_arraylist_pop(list));

  /* remove item in middle of list */
  CU_ASSERT_EQUAL(data1, np_arraylist_push(list, data1));
  CU_ASSERT_EQUAL(data2, np_arraylist_push(list, data2));
  CU_ASSERT_EQUAL(data3, np_arraylist_push(list, data3));
  CU_ASSERT_EQUAL(3, np_arraylist_length(list));
  CU_ASSERT_EQUAL(data2, np_arraylist_remove(list, 1));
  CU_ASSERT_EQUAL(2, np_arraylist_length(list));
  CU_ASSERT_EQUAL(data3, np_arraylist_pop(list));
  CU_ASSERT_EQUAL(data1, np_arraylist_pop(list));

  /* remove item past the end of the list */
  CU_ASSERT_EQUAL(data1, np_arraylist_push(list, data1));
  CU_ASSERT_EQUAL(data2, np_arraylist_push(list, data2));
  CU_ASSERT_EQUAL(2, np_arraylist_length(list));
  CU_ASSERT_EQUAL(NULL, np_arraylist_remove(list, 2));
  CU_ASSERT_EQUAL(NULL, np_arraylist_remove(list, 3));
  CU_ASSERT_EQUAL(NULL, np_arraylist_remove(list, 99));

  np_arraylist_free(list);
}

void np_arraylist_test_get(void)
{
  struct NpArrayList *list;
  char *data1 = "The first data item";
  char *data2 = "The second data item";

  list = np_arraylist_new();

  /* get item from empty list */
  CU_ASSERT_EQUAL(NULL, np_arraylist_get(list, 0));
  CU_ASSERT_EQUAL(NULL, np_arraylist_get(list, 1));
  CU_ASSERT_EQUAL(NULL, np_arraylist_get(list, 99));

  /* single item */
  CU_ASSERT_EQUAL(data1, np_arraylist_push(list, data1));
  CU_ASSERT_EQUAL(data1, np_arraylist_get(list, 0));
  CU_ASSERT_EQUAL(NULL, np_arraylist_get(list, 1));
  CU_ASSERT_EQUAL(NULL, np_arraylist_get(list, 99));

  /* multiple items */
  CU_ASSERT_EQUAL(data2, np_arraylist_push(list, data2));
  CU_ASSERT_EQUAL(data1, np_arraylist_get(list, 1));
  CU_ASSERT_EQUAL(data2, np_arraylist_get(list, 0));
  CU_ASSERT_EQUAL(NULL, np_arraylist_get(list, 2));
  CU_ASSERT_EQUAL(NULL, np_arraylist_get(list, 99));

  np_arraylist_free(list);
}

void np_arraylist_test_iterator(void)
{
  struct NpArrayList *list;
  struct NpArrayListIterator *iter;
  char *data1 = "The first data item";
  char *data2 = "The second data item";

  list = np_arraylist_new();

  /* get iterator for empty list */
  iter = np_arraylist_iterator(list);
  CU_ASSERT_EQUAL(NULL, np_arraylist_iterator_next(iter));
  CU_ASSERT_EQUAL(NULL, np_arraylist_iterator_next(iter));
  np_arraylist_iterator_free(iter);

  /* single item */
  CU_ASSERT_EQUAL(data1, np_arraylist_push(list, data1));
  iter = np_arraylist_iterator(list);
  CU_ASSERT_EQUAL(data1, np_arraylist_iterator_next(iter));
  CU_ASSERT_EQUAL(NULL, np_arraylist_iterator_next(iter));
  np_arraylist_iterator_free(iter);

  /* multiple items */
  CU_ASSERT_EQUAL(data2, np_arraylist_push(list, data2));
  iter = np_arraylist_iterator(list);
  CU_ASSERT_EQUAL(data2, np_arraylist_iterator_next(iter));
  CU_ASSERT_EQUAL(data1, np_arraylist_iterator_next(iter));
  CU_ASSERT_EQUAL(NULL, np_arraylist_iterator_next(iter));
  np_arraylist_iterator_free(iter);

  np_arraylist_free(list);
}

void np_arraylist_test_realloc(void)
{
  struct NpArrayList *list;
  char *data = "The data item";
  int i;

  list = np_arraylist_new();
  for (i = 0; i < NP_ARRAYLIST_DEFAULT_ALLOC_SIZE + 1; ++i)
    CU_ASSERT_EQUAL(data, np_arraylist_push(list, data));
  CU_ASSERT_EQUAL(NP_ARRAYLIST_DEFAULT_ALLOC_SIZE * 2, list->allocated);
  CU_ASSERT_EQUAL(NP_ARRAYLIST_DEFAULT_ALLOC_SIZE + 1, list->size);
}

