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

#include "fd_ht.h"
#include "fd_common.h"

#include <assert.h>
#include <stdlib.h>

fd_ret_t fd_ht_init(fd_ht_t* ht, fd_cmp_t cmp, fd_hash_t hash, int capacity) {
  if (!ht || !cmp || !hash || capacity < 1) {
    return FD_EARG;
  }

  fd_key_value_t** buckets =
      (fd_key_value_t**)FD_CALLOC(capacity, fd_key_value_t);
  ht->buckets = buckets;
  ht->hash = hash;
  ht->cmp = cmp;
  ht->capacity = capacity;
  return FD_OK;
}

fd_ret_t fd_ht_destroy(fd_ht_t* ht) {
  if (!ht) {
    return FD_EARG;
  }

  ht->hash = NULL;
  ht->cmp = NULL;
  for (int bucket = 0; bucket < ht->capacity; bucket++) {
    fd_key_value_t* e = ht->buckets[bucket];
    while (e) {
      fd_key_value_t* tmp = e->next;
      free(e);
      e = tmp;
    }
  }
  free(ht->buckets);
  ht->buckets = NULL;
  ht->capacity = 0;
  return FD_OK;
}

static fd_ret_t fd_key_value_init(fd_key_value_t* kv, void* k, void* v,
                                  fd_key_value_t* next) {
  if (!kv || !k) {
    return FD_EARG;
  }
  kv->k = k;
  kv->v = v;
  kv->next = next;
  return FD_OK;
}

static fd_key_value_t* fd_ht_find(fd_ht_t* ht, void* k, int bucket) {
  fd_key_value_t* e = ht->buckets[bucket];
  while (e) {
    if (0 == ht->cmp(k, e->k)) {
      return e;
    }
    e = e->next;
  }
  return NULL;
}

fd_ret_t fd_ht_put(fd_ht_t* ht, void* k, void* v) {
  if (!ht || !k) {
    return FD_EARG;
  }

  int bucket = ht->hash(k);
  fd_key_value_t* kv = fd_ht_find(ht, k, bucket);
  if (kv) {
    kv->v = v;
    return FD_OK;
  }

  kv = FD_MALLOC(fd_key_value_t);
  int ret = fd_key_value_init(kv, k, v, ht->buckets[bucket]);
  assert(FD_OK == ret);
  ht->buckets[bucket] = kv;
  return FD_OK;
}

fd_ret_t fd_ht_get(fd_ht_t* ht, void* k, void** v) {
  if (!ht || !k) {
    return FD_EARG;
  }

  int bucket = ht->hash(k);
  fd_key_value_t* e = ht->buckets[bucket];
  for (fd_key_value_t* e = ht->buckets[bucket]; e && 0 != ht->cmp(e->k, k);
       e = e->next)
    ;

  if (!e) {
    return FD_NOT_FOUND;
  }

  *v = e->v;
  return FD_OK;
}

fd_ret_t fd_ht_remove(fd_ht_t* ht, void* k, void** v) {
  if (!ht || !k) {
    return FD_EARG;
  }

  int bucket = ht->hash(k);
  fd_key_value_t* e = ht->buckets[bucket];
  if (!e) {
    return FD_NOT_FOUND;
  }

  if (0 == ht->cmp(k, e->k)) {
    ht->buckets[bucket] = e->next;
    *v = e->v;
    free(e);
    return FD_OK;
  }

  while (e->next && 0 != ht->cmp(k, e->next->k)) {
    e = e->next;
  }

  if (!e->next) {
    return FD_NOT_FOUND;
  }
  fd_key_value_t* tmp = e->next->next;
  *v = e->next->v;
  free(e->next);
  e->next = tmp;
  return FD_OK;
}
