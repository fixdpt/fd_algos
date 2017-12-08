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
#include "fd_ret.h"
#include "unity.h"

typedef struct e {
  int x;
} e;

void test_enqueue(void) {
  fd_bounded_q_t q;
  fd_bounded_q_init(&q, 4);
  TEST_ASSERT(FD_EARG == fd_bounded_q_enqueue(&q, NULL));
  e a = {1};
  TEST_ASSERT(FD_OK == fd_bounded_q_enqueue(&q, &a));
  TEST_ASSERT(FD_OK == fd_bounded_q_enqueue(&q, &a));
  TEST_ASSERT(FD_OK == fd_bounded_q_enqueue(&q, &a));
  TEST_ASSERT(FD_OK == fd_bounded_q_enqueue(&q, &a));
  TEST_ASSERT(FD_FULL == fd_bounded_q_enqueue(&q, &a));
  fd_bounded_q_destroy(&q);
}

void test_dequeue(void) {
  fd_bounded_q_t q;
  fd_bounded_q_init(&q, 4);
  void* e_out = NULL;
  TEST_ASSERT(FD_EMPTY == fd_bounded_q_dequeue(&q, &e_out));
  e a = {1};
  fd_bounded_q_enqueue(&q, &a);
  e b = {2};
  fd_bounded_q_enqueue(&q, &b);
  e c = {3};
  fd_bounded_q_enqueue(&q, &c);
  e d = {4};
  fd_bounded_q_enqueue(&q, &d);
  TEST_ASSERT(FD_OK == fd_bounded_q_dequeue(&q, &e_out));
  TEST_ASSERT(1 == ((e*)e_out)->x);
  TEST_ASSERT(FD_OK == fd_bounded_q_dequeue(&q, &e_out));
  TEST_ASSERT(2 == ((e*)e_out)->x);
  TEST_ASSERT(FD_OK == fd_bounded_q_dequeue(&q, &e_out));
  TEST_ASSERT(3 == ((e*)e_out)->x);
  TEST_ASSERT(FD_OK == fd_bounded_q_dequeue(&q, &e_out));
  TEST_ASSERT(4 == ((e*)e_out)->x);
  TEST_ASSERT(FD_EMPTY == fd_bounded_q_dequeue(&q, &e_out));
  fd_bounded_q_destroy(&q);
}

void test_enqueue_dequeue(void) {
  fd_bounded_q_t q;
  fd_bounded_q_init(&q, 4);
  void* e_out = NULL;
  TEST_ASSERT(FD_EMPTY == fd_bounded_q_dequeue(&q, &e_out));
  e a = {1};
  fd_bounded_q_enqueue(&q, &a);
  e b = {2};
  fd_bounded_q_enqueue(&q, &b);
  e c = {3};
  fd_bounded_q_enqueue(&q, &c);
  e d = {4};
  fd_bounded_q_enqueue(&q, &d);
  TEST_ASSERT(FD_OK == fd_bounded_q_dequeue(&q, &e_out));
  TEST_ASSERT(1 == ((e*)e_out)->x);
  TEST_ASSERT(FD_OK == fd_bounded_q_dequeue(&q, &e_out));
  TEST_ASSERT(2 == ((e*)e_out)->x);
  e f = {5};
  fd_bounded_q_enqueue(&q, &f);
  e g = {6};
  fd_bounded_q_enqueue(&q, &g);
  TEST_ASSERT(FD_OK == fd_bounded_q_dequeue(&q, &e_out));
  TEST_ASSERT(3 == ((e*)e_out)->x);
  TEST_ASSERT(FD_OK == fd_bounded_q_dequeue(&q, &e_out));
  TEST_ASSERT(4 == ((e*)e_out)->x);
  TEST_ASSERT(FD_OK == fd_bounded_q_dequeue(&q, &e_out));
  TEST_ASSERT(5 == ((e*)e_out)->x);
  TEST_ASSERT(FD_OK == fd_bounded_q_dequeue(&q, &e_out));
  TEST_ASSERT(6 == ((e*)e_out)->x);
  TEST_ASSERT(FD_EMPTY == fd_bounded_q_dequeue(&q, &e_out));
  fd_bounded_q_enqueue(&q, &g);
  TEST_ASSERT(FD_OK == fd_bounded_q_dequeue(&q, &e_out));
  TEST_ASSERT(6 == ((e*)e_out)->x);
  fd_bounded_q_destroy(&q);
  TEST_ASSERT(0 == q.capacity);
  TEST_ASSERT(0 == q.head);
  TEST_ASSERT(0 == q.tail);
  TEST_ASSERT(!q.buf);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_enqueue);
  RUN_TEST(test_dequeue);
  RUN_TEST(test_enqueue_dequeue);
  return UNITY_END();
}
