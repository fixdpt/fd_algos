/*
 * Copyright 2017 Granville Barnett
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef FD_HT_H
#define FD_HT_H

#include "fd_common.h"
#include "fd_ret.h"

/*
 * Hash table with linear chaining.
 *
 * Assuming a hash function that relatively unitformly distributes keys and the
 * hash table having a load factor <= 1, puts and get should be O(1). For hash
 * tables where the load factory slightly exceeds 1, puts and gets will be O(n)
 * where n is relatively small.
 *
 */
typedef struct fd_key_value {
  void* k;
  void* v;
  struct fd_key_value* next;
} fd_key_value_t;

typedef struct fd_ht {
  int capacity;
  fd_hash_t hash;
  fd_cmp_t cmp;
  fd_key_value_t** buckets;
} fd_ht_t;

/**
 * Initialises the hash map with the specified capactiy.
 *
 * @param[in] ht
 * @param[in] cmp
 * @param[in] hash
 * @param[in] capacity
 */
fd_ret_t fd_ht_init(fd_ht_t* ht, fd_cmp_t cmp, fd_hash_t hash, int capacity);
/**
 * Destroys the hash map.
 *
 * @param[in] ht
 */
fd_ret_t fd_ht_destroy(fd_ht_t* ht);
/**
 * Puts the key-value pair.
 *
 * @param[in] ht
 * @param[in] k
 * @param[in] v
 */
fd_ret_t fd_ht_put(fd_ht_t* ht, void* k, void* v);
/**
 * Gets the value associated with the key.
 *
 * @param[in] ht
 * @param[in] k
 * @param[out] v
 */
fd_ret_t fd_ht_get(fd_ht_t* ht, void* k, void** v);
/**
 * Removes the key-value pair with the specified key.
 *
 * @param[in] ht
 * @param[in] k
 * @param[out] v
 */
fd_ret_t fd_ht_remove(fd_ht_t* ht, void* k, void** v);

#endif
