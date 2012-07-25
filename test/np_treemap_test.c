/*
 * np_treemap_test.c: nplib tree map tests
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

#include "np_treemap_test.h"
#include "np_treemap.h"

void np_treemap_test(void)
{
  struct NpTreeMap *map;
  char *key = "key";
  char *value = "value";
  char *value2 = "value2";

  /* single value */
  CU_ASSERT_NOT_EQUAL(NULL, map = np_treemap_new(np_treemap_test_cmp));
  CU_ASSERT_EQUAL(value, np_treemap_put(map, key, value));
  CU_ASSERT_EQUAL(value, np_treemap_get(map, key));

  /* replace existing value */
  CU_ASSERT_EQUAL(value2, np_treemap_put(map, key, value2));
  CU_ASSERT_EQUAL(value2, np_treemap_get(map, key));

  /* delete node */
  CU_ASSERT_EQUAL(value2, np_treemap_remove(map, key));
  CU_ASSERT_EQUAL(NULL, np_treemap_remove(map, key));

  np_treemap_free(map);
}

void np_treemap_test_iterator(void)
{
  struct NpTreeMap *map;
  struct NpTreeMapIterator *iter;
  char *key1 = "a key1";
  char *key2 = "b key2";
  char *key3 = "c key3";
  char *value1 = "value 1";
  char *value2 = "value 2";
  char *value3 = "value 3";

  CU_ASSERT_NOT_EQUAL(NULL, map = np_treemap_new(np_treemap_test_cmp));

  CU_ASSERT_EQUAL(value1, np_treemap_put(map, key1, value1));
  CU_ASSERT_EQUAL(value1, np_treemap_get(map, key1));
  CU_ASSERT_EQUAL(value2, np_treemap_put(map, key2, value2));
  CU_ASSERT_EQUAL(value2, np_treemap_get(map, key2));
  CU_ASSERT_EQUAL(value3, np_treemap_put(map, key3, value3));
  CU_ASSERT_EQUAL(value3, np_treemap_get(map, key3));

  /* iterate */
  CU_ASSERT_NOT_EQUAL(NULL, iter = np_treemap_iterator(map));

  CU_ASSERT_EQUAL(key1, np_treemap_iterator_peek_next_key(iter));
  CU_ASSERT_EQUAL(value1, np_treemap_iterator_peek_next_value(iter));
  CU_ASSERT_EQUAL(key1, np_treemap_iterator_next_key(iter));

  CU_ASSERT_EQUAL(key2, np_treemap_iterator_peek_next_key(iter));
  CU_ASSERT_EQUAL(value2, np_treemap_iterator_peek_next_value(iter));
  CU_ASSERT_EQUAL(key2, np_treemap_iterator_next_key(iter));

  CU_ASSERT_EQUAL(key3, np_treemap_iterator_peek_next_key(iter));
  CU_ASSERT_EQUAL(value3, np_treemap_iterator_peek_next_value(iter));
  CU_ASSERT_EQUAL(key3, np_treemap_iterator_next_key(iter));

  CU_ASSERT_EQUAL(NULL, np_treemap_iterator_peek_next_key(iter));
  CU_ASSERT_EQUAL(NULL, np_treemap_iterator_peek_next_value(iter));
  CU_ASSERT_EQUAL(NULL, np_treemap_iterator_next_key(iter));

  np_treemap_iterator_free(iter);

  np_treemap_free(map);

}

int np_treemap_test_cmp(void *key1, void *key2)
{
  return strcmp(key1, key2);
}
