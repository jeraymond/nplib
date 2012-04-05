/*
 * np_dict_test.c: nplib dictionary tests
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

#include "np_dict_test.h"
#include "np_dict.h"

void np_dict_test(void) {
  struct NpDict *dict;
  char *key = "thekey";
  char *value = "thevalue";

  CU_ASSERT_NOT_EQUAL(NULL, dict = np_dict_new(np_dict_test_cmp,
					       np_dict_test_hash));
  CU_ASSERT_STRING_EQUAL(value, np_dict_put(dict, key, value));
  CU_ASSERT_STRING_EQUAL(value, (char *)np_dict_get(dict, key));
  CU_ASSERT_STRING_EQUAL(value, (char *)np_dict_remove(dict, key));
  CU_ASSERT_EQUAL(NULL, np_dict_get(dict, key));
  np_dict_free(dict);
}

int np_dict_test_cmp(void *key1, void *key2)
{
  return strcmp(key1, key2);
}

unsigned np_dict_test_hash(void *key)
{
  int length = strlen(key);
  return np_dict_hash(key, length);
}
