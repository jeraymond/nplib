/*
 * np_hashmap.c: nplib hash map
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
#include "np_hashmap.h"

struct NpHashMap *np_hashmap_new(int (*key_compare)(void *key1, void *key2),
                            unsigned (*key_hash)(void *key))
{
  struct NpHashMap *map;
  int i;
  int size;

  size = HASHMAP_SIZE;
  map = malloc(sizeof *map);
  if (map != NULL) {
    if ((map->items = malloc(sizeof *map->items * size)) != NULL) {
      map->key_compare = key_compare;
      map->key_hash = key_hash;
      map->size = size;
      for (i = 0; i < size; ++i)
	map->items[i] = NULL;
    } else {
      free(map);
      return NULL;
    }
  }
  return map;
}

void np_hashmap_free(struct NpHashMap *map)
{
  struct NpHashMapItem *item;
  struct NpHashMapItem *next;
  unsigned i;

  for (i = 0; i < map->size; ++i) {
    if ((item = map->items[i]) == NULL)
      continue;
    while(item) {
      next = item->next;
      free(item);
      item = next;
    }
  }
  free(map->items);
  free(map);
}

void *np_hashmap_put(struct NpHashMap *map, void *key, void *value)
{
  struct NpHashMapItem *item;
  int i;;

  i = map->key_hash(key) % map->size;
  for (item = map->items[i]; item != NULL; item = item->next)
    if (map->key_compare(key, item->key) == 0)
      break;
  if (item == NULL) {
    item = malloc(sizeof *item);
    if (item == NULL) {
      return NULL;
    } else {
      item->key = key;
      item->value = value;
      item->next = map->items[i];
      map->items[i] = item;
    }
  } else {
    item->value = value;
  }
  return value;
}

void *np_hashmap_get(struct NpHashMap *map, void *key)
{
  struct NpHashMapItem *item;
  int i;

  i = map->key_hash(key) % map->size;
  for (item = map->items[i]; item != NULL; item = item->next)
    if (map->key_compare(key, item->key) == 0)
      return item->value;
  return NULL;
}

void *np_hashmap_remove(struct NpHashMap *map, void *key)
{
  struct NpHashMapItem *prev;
  struct NpHashMapItem *item;
  void *ret;
  int i;

  ret = NULL;
  prev = NULL;
  i = map->key_hash(key) % map->size;
  for (item = map->items[i]; item != NULL; prev = item, item = item->next)
    if (map->key_compare(key, item->key) == 0) {
      ret = item->value;
      if (prev != NULL)
	prev->next = item->next;
      else
	map->items[i] = NULL;
      free(item);
    }
  return ret;
}

unsigned np_hashmap_hash(void *key, int length)
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
