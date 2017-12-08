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

#ifndef FD_BOUNDED_Q_H
#define FD_BOUNDED_Q_H

#include "fd_ret.h"

typedef struct fd_bounded_q_t {
  int head, tail, capacity;
  void** buf;
} fd_bounded_q_t;

/**
 * Initialises a bounded queue with the specified capacity.
 *
 * @param[in] q
 * @param[in] capacity
 */
fd_ret_t fd_bounded_q_init(fd_bounded_q_t* q, int capacity);
/**
 * Enqueues the element into the queue.
 *
 * @param[in] q
 * @param[in] e Cannot be NULL
 */
fd_ret_t fd_bounded_q_enqueue(fd_bounded_q_t* q, void* e);
/**
 * Dequeues the head of the queue.
 *
 * @param[in] q
 * @param[out] e
 */
fd_ret_t fd_bounded_q_dequeue(fd_bounded_q_t* q, void** e);

/**
 * Destroys the queue.
 *
 * @param[in] q
 */
fd_ret_t fd_bounded_q_destroy(fd_bounded_q_t* q);

#endif
