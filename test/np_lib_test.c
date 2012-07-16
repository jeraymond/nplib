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

#include "np_dict_test.h"
#include "np_linkedlist_test.h"

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
  if (CU_add_test(pSuite, "Dict Tests", np_dict_test) == NULL) {
    goto exit;
  }
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

