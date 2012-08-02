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
  unsigned i;
  unsigned capacity;

  capacity = NP_HASHMAP_INITIAL_CAPACITY;
  map = malloc(sizeof *map);
  if (map != NULL) {
    if ((map->items = malloc(sizeof *map->items * capacity)) != NULL) {
      map->key_compare = key_compare;
      map->key_hash = key_hash;
      map->capacity = capacity;
      map->size = 0;
      map->load_factor = NP_HASHMAP_DEFAULT_LOAD_FACTOR;
      map->threshold = map->capacity * map->load_factor;
      for (i = 0; i < capacity; ++i)
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

  for (i = 0; i < map->capacity; ++i) {
    if ((item = map->items[i]) == NULL)
      continue;
    while (item) {
      next = item->next;
      free(item);
      item = next;
    }
  }
  free(map->items);
  free(map);
}

static struct NpHashMap *np_hashmap_realloc(struct NpHashMap *map)
{
  if (map->size == map->threshold) {
    struct NpHashMap new_map;
    struct NpHashMapItem *item;
    struct NpHashMapItem *next;
    unsigned new_capacity;
    unsigned i;

    new_capacity = map->capacity * 2;
    if ((new_map.items = malloc(sizeof *new_map.items * new_capacity)) == NULL)
      return NULL;
    new_map.key_compare = map->key_compare;
    new_map.key_hash = map->key_hash;
    new_map.capacity = new_capacity;
    new_map.size = 0;
    new_map.load_factor = map->load_factor;
    new_map.threshold = new_capacity * new_map.load_factor;
    for (i = 0; i < new_capacity; ++i)
      new_map.items[i] = NULL;

    for (i = 0; i < map->capacity; ++i) {
      if ((item = map->items[i]) == NULL)
	continue;
      while (item) {
	next = item->next;
	np_hashmap_put(&new_map, item->key, item->value);
	free(item);
	item = next;
      }
    }
    free(map->items);
    map->items = new_map.items;
    map->capacity = new_capacity;
    map->threshold = new_map.threshold;
  }
  return map;
}

void *np_hashmap_put(struct NpHashMap *map, void *key, void *value)
{
  struct NpHashMapItem *item;
  unsigned i;

  map = np_hashmap_realloc(map);
  if (map == NULL)
    return NULL;
  i = map->key_hash(key) % map->capacity;
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
      map->size++;
    }
  } else {
    item->value = value;
  }
  return value;
}

void *np_hashmap_get(struct NpHashMap *map, void *key)
{
  struct NpHashMapItem *item;
  unsigned i;

  i = map->key_hash(key) % map->capacity;
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
  unsigned i;

  ret = NULL;
  prev = NULL;
  i = map->key_hash(key) % map->capacity;
  for (item = map->items[i]; item != NULL; prev = item, item = item->next)
    if (map->key_compare(key, item->key) == 0) {
      ret = item->value;
      if (prev != NULL)
	prev->next = item->next;
      else
	map->items[i] = NULL;
      free(item);
      map->size--;
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
