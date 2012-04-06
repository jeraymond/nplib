/*
 * np_linkedlist_test.c: nplib linked list tests
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

#include "np_linkedlist_test.h"
#include "np_linkedlist.h"

void np_linkedlist_test(void) {
  struct NpLinkedList *list;
  char *data1 = "The first data item";
  char *data2 = "The second data item";

  /* push and pop */
  CU_ASSERT_NOT_EQUAL(NULL, list = np_linkedlist_new());
  CU_ASSERT_STRING_EQUAL(data1, np_linkedlist_push(list, data1));
  CU_ASSERT_STRING_EQUAL(data1, np_linkedlist_pop(list));
  CU_ASSERT_EQUAL(NULL, np_linkedlist_pop(list));
  CU_ASSERT_STRING_EQUAL(data1, np_linkedlist_push(list, data1));
  CU_ASSERT_STRING_EQUAL(data2, np_linkedlist_push(list, data2));
  CU_ASSERT_STRING_EQUAL(data2, np_linkedlist_pop(list));
  CU_ASSERT_STRING_EQUAL(data1, np_linkedlist_pop(list));
  CU_ASSERT_EQUAL(NULL, np_linkedlist_pop(list));

  /* reverse */
  np_linkedlist_reverse(list);
  CU_ASSERT_EQUAL(NULL, np_linkedlist_pop(list));

  np_linkedlist_push(list, data1);
  np_linkedlist_reverse(list);
  CU_ASSERT_STRING_EQUAL(data1, np_linkedlist_pop(list));
  CU_ASSERT_EQUAL(NULL, np_linkedlist_pop(list));

  np_linkedlist_push(list, data1);
  np_linkedlist_push(list, data2);
  np_linkedlist_reverse(list);
  CU_ASSERT_STRING_EQUAL(data1, np_linkedlist_pop(list));
  CU_ASSERT_STRING_EQUAL(data2, np_linkedlist_pop(list));
  CU_ASSERT_EQUAL(NULL, np_linkedlist_pop(list));

  /* length */
  CU_ASSERT_EQUAL(0, np_linkedlist_length(list));
  np_linkedlist_push(list, data1);
  CU_ASSERT_EQUAL(1, np_linkedlist_length(list));
  np_linkedlist_push(list, data1);
  CU_ASSERT_EQUAL(2, np_linkedlist_length(list));

  np_linkedlist_free(list);
}
