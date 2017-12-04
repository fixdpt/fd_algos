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
 */

#ifndef FD_COMMON_H
#define FD_COMMON_H

#include <assert.h>
#include <stdlib.h>

static inline void* fd_malloc(size_t size) {
  void* mem = malloc(size);
  assert(mem);
  return mem;
}
#define FD_MALLOC(type) fd_malloc(sizeof(type))

static inline void* fd_calloc(size_t nmemb, size_t size) {
  void* mem = calloc(nmemb, size);
  assert(mem);
  return mem;
}
#define FD_CALLOC(nmemb, type) fd_calloc((nmemb), sizeof(type))

typedef int (*fd_hash_t)(void*);
typedef int (*fd_cmp_t)(void*, void*);

#endif
