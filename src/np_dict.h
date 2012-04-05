/*
 * np_dict.h: nplib dictionary header file
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

#ifndef __NP_DICT_H
#define __NP_DICT_H

#define DICT_SIZE 256

struct NpDict {
  int (*key_compare)(void *key1, void *key2);
  unsigned (*key_hash)(void *key);
  unsigned size;
  struct NpDictItem **items;
};

struct NpDictItem {
  void *key;
  void *value;
  struct NpDictItem *next;
};

struct NpDict *np_dict_new(int (*cmp)(void *key1, void *key2),
                            unsigned (*hash)(void *key));
void np_dict_free(struct NpDict *dict);
void *np_dict_put(struct NpDict *dict, void *key, void *value);
void *np_dict_get(struct NpDict *dict, void *key);
void *np_dict_remove(struct NpDict *dict, void *key);
unsigned np_dict_hash(void *key, int length);

#endif
