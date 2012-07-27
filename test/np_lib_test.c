/*
 * np_lib_test.c: nplib test program
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

#include "np_hashmap_test.h"
#include "np_treemap_test.h"
#include "np_linkedlist_test.h"
#include "np_arraylist_test.h"

int setup(void);
int teardown(void);

int main(void)
{
  CU_pSuite pSuite = NULL;

  if (CU_initialize_registry() != CUE_SUCCESS) {
    return CU_get_error();
  }
  pSuite = CU_add_suite("Unit Tests", setup, teardown);
  if (pSuite == NULL) {
    goto exit;
  }

  /* hash map */
  if (CU_add_test(pSuite, "Hash Map Tests", np_hashmap_test) == NULL) {
    goto exit;
  }

  /* tree map */
  if (CU_add_test(pSuite, "Tree Map Tests", np_treemap_test) == NULL) {
    goto exit;
  }
  if (CU_add_test(pSuite, "Tree Map Iterator Tests",
		  np_treemap_test_iterator) == NULL) {
    goto exit;
  }

  /* linked list */
  if (CU_add_test(pSuite, "Linked List Basic Tests",
		  np_linkedlist_test_basics) == NULL) {
    goto exit;
  }
  if (CU_add_test(pSuite, "Linked List Add Tests",
		  np_linkedlist_test_add) == NULL) {
    goto exit;
  }
  if (CU_add_test(pSuite, "Linked List Remove Tests",
		  np_linkedlist_test_remove) == NULL) {
    goto exit;
  }
  if (CU_add_test(pSuite, "Linked List Get Tests",
		  np_linkedlist_test_get) == NULL) {
    goto exit;
  }
  if (CU_add_test(pSuite, "Linked List Iterator Tests",
		  np_linkedlist_test_iterator) == NULL) {
    goto exit;
  }

  /* array list */
  if (CU_add_test(pSuite, "Array List Basic Tests",
		  np_arraylist_test_basics) == NULL) {
    goto exit;
  }
  if (CU_add_test(pSuite, "Array List Add Tests",
		  np_arraylist_test_add) == NULL) {
    goto exit;
  }
  if (CU_add_test(pSuite, "Array List Remove Tests",
		  np_arraylist_test_remove) == NULL) {
    goto exit;
  }
  if (CU_add_test(pSuite, "Array List Get Tests",
		  np_arraylist_test_get) == NULL) {
    goto exit;
  }
  if (CU_add_test(pSuite, "Array List Iterator Tests",
		  np_arraylist_test_iterator) == NULL) {
    goto exit;
  }
  if (CU_add_test(pSuite, "Array List Realloc Tests",
		  np_arraylist_test_realloc) == NULL) {
    goto exit;
  }

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();

 exit:
  CU_cleanup_registry();
  return CU_get_error();
}

int setup(void)
{
  return 0;
}

int teardown(void)
{
  return 0;
}

