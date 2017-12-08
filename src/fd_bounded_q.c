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

#include "fd_bounded_q.h"
#include "fd_common.h"

#define FD_BQ_NEXT_INDEX(i, capacity) ((i) + 1) % (capacity)
#define FD_BQ_EMPTY(q) !(q)->buf[(q)->head]
#define FD_BQ_FULL(q) (q)->buf[(q)->tail]

fd_ret_t fd_bounded_q_init(fd_bounded_q_t* q, int capacity) {
  if (!q || capacity < 0) {
    return FD_EARG;
  }

  q->head = q->tail = 0;
  q->capacity = capacity;
  q->buf = (void**)FD_CALLOC(capacity, void*);
  return FD_OK;
}

fd_ret_t fd_bounded_q_enqueue(fd_bounded_q_t* q, void* e) {
  if (!q || !e) {
    return FD_EARG;
  }

  if (FD_BQ_FULL(q)) {
    return FD_FULL;
  }

  q->buf[q->tail] = e;
  q->tail = FD_BQ_NEXT_INDEX(q->tail, q->capacity);
  return FD_OK;
}

fd_ret_t fd_bounded_q_dequeue(fd_bounded_q_t* q, void** e) {
  if (!q || !e) {
    return FD_EARG;
  }

  if (FD_BQ_EMPTY(q)) {
    return FD_EMPTY;
  }

  *e = q->buf[q->head];
  q->buf[q->head] = NULL;
  q->head = FD_BQ_NEXT_INDEX(q->head, q->capacity);
  return FD_OK;
}

fd_ret_t fd_bounded_q_destroy(fd_bounded_q_t* q) {
  if (!q) {
    return FD_EARG;
  }

  q->head = q->tail = q->capacity = 0;
  free(q->buf);
  q->buf = NULL;
  return FD_OK;
}
