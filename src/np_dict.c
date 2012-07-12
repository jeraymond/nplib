/*
 * np_dict.c: nplib dictionary
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
#include "np_dict.h"

struct NpDict *np_dict_new(int (*key_compare)(void *key1, void *key2),
                            unsigned (*key_hash)(void *key))
{
  struct NpDict *dict;
  int i;
  int size;

  size = DICT_SIZE;
  dict = malloc(sizeof *dict);
  if (dict != NULL) {
    if ((dict->items = malloc(sizeof *dict->items * size)) != NULL) {
      dict->key_compare = key_compare;
      dict->key_hash = key_hash;
      dict->size = size;
      for (i = 0; i < size; ++i)
	dict->items[i] = NULL;
    } else {
      free(dict);
      return NULL;
    }
  }
  return dict;
}

void np_dict_free(struct NpDict *dict)
{
  struct NpDictItem *item;
  struct NpDictItem *next;
  unsigned i;

  for (i = 0; i < dict->size; ++i) {
    if ((item = dict->items[i]) == NULL)
      continue;
    while(item) {
      next = item->next;
      free(item);
      item = next;
    }
  }
  free(dict->items);
  free(dict);
}

void *np_dict_put(struct NpDict *dict, void *key, void *value)
{
  struct NpDictItem *item;
  int i;;

  i = dict->key_hash(key) % dict->size;
  for (item = dict->items[i]; item != NULL; item = item->next)
    if (dict->key_compare(key, item->key) == 0)
      break;
  if (item == NULL) {
    item = malloc(sizeof *item);
    if (item == NULL) {
      return NULL;
    } else {
      item->key = key;
      item->value = value;
      item->next = dict->items[i];
      dict->items[i] = item;
    }
  } else {
    item->value = value;
  }
  return value;
}

void *np_dict_get(struct NpDict *dict, void *key)
{
  struct NpDictItem *item;
  int i;

  i = dict->key_hash(key) % dict->size;
  for (item = dict->items[i]; item != NULL; item = item->next)
    if (dict->key_compare(key, item->key) == 0)
      return item->value;
  return NULL;
}

void *np_dict_remove(struct NpDict *dict, void *key)
{
  struct NpDictItem *prev;
  struct NpDictItem *item;
  void *ret;
  int i;

  ret = NULL;
  prev = NULL;
  i = dict->key_hash(key) % dict->size;
  for (item = dict->items[i]; item != NULL; prev = item, item = item->next)
    if (dict->key_compare(key, item->key) == 0) {
      ret = item->value;
      if (prev != NULL)
	prev->next = item->next;
      else
	dict->items[i] = NULL;
      free(item);
    }
  return ret;
}

unsigned np_dict_hash(void *key, int length)
{
 /*  Bob Jenkins, one-at-a-time hash */
  unsigned char *p = key;
  unsigned h = 0;
  int i;

  for (i = 0; i < length; ++i) {
    h += p[i];
    h += (h << 10);
    h ^= (h >> 6);
  }
  h += (h << 3);
  h ^= (h >> 11);
  h += (h << 15);
  return h;
}
