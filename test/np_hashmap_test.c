/*
 * np_hashmap_test.c: nplib hash map tests
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
#include <stdlib.h>

#include "np_hashmap_test.h"
#include "np_hashmap.h"
#include "np_arraylist.h"

void np_hashmap_test(void)
{
  struct NpHashMap *map;
  char *key = "thekey";
  char *value = "thevalue";
  char *value2 = "thevalue2";

  CU_ASSERT_NOT_EQUAL(NULL, map = np_hashmap_new(np_hashmap_test_cmp,
						 np_hashmap_test_hash));
  CU_ASSERT_EQUAL(0, map->size);
  CU_ASSERT_STRING_EQUAL(value, np_hashmap_put(map, key, value));
  CU_ASSERT_EQUAL(1, map->size);
  CU_ASSERT_STRING_EQUAL(value, np_hashmap_get(map, key));
  CU_ASSERT_EQUAL(1, map->size);
  CU_ASSERT_STRING_EQUAL(value2, np_hashmap_put(map, key, value2));
  CU_ASSERT_EQUAL(1, map->size);
  CU_ASSERT_STRING_EQUAL(value2, np_hashmap_remove(map, key));
  CU_ASSERT_EQUAL(0, map->size);
  CU_ASSERT_EQUAL(NULL, np_hashmap_get(map, key));
  np_hashmap_free(map);
}

void np_hashmap_realloc_test(void)
{
  struct NpArrayList *key_list;
  struct NpHashMap *map;
  unsigned i;
  unsigned size;
  char *key_prefix = "key %d";

  key_list = np_arraylist_new();
  CU_ASSERT_NOT_EQUAL(NULL, map = np_hashmap_new(np_hashmap_test_cmp,
						 np_hashmap_test_hash));
  size = map->threshold + 1;
  for (i = 0; i < size; ++i) {
    char *key = malloc(BUFSIZ);
    snprintf(key, BUFSIZ, key_prefix, i);
    np_arraylist_add(key_list, key, i);
    CU_ASSERT_EQUAL(key, np_hashmap_put(map, key, key));
  }

  CU_ASSERT_EQUAL(NP_HASHMAP_INITIAL_CAPACITY * 2, map->capacity);
  CU_ASSERT_EQUAL(map->capacity * map->load_factor, map->threshold);
  for (i = size - 1; i <= size; --i) {
    char *key;

    key = np_arraylist_get(key_list, i);
    CU_ASSERT_EQUAL(key, np_hashmap_remove(map, key));
    CU_ASSERT_EQUAL(key, np_arraylist_remove(key_list, i))
    free(key);
  }
  CU_ASSERT_EQUAL(0, map->size);
  np_arraylist_free(key_list);
  np_hashmap_free(map);
}

int np_hashmap_test_cmp(void *key1, void *key2)
{
  return strcmp(key1, key2);
}

unsigned np_hashmap_test_hash(void *key)
{
  int length = strlen(key);
  return np_hashmap_hash(key, length);
}
