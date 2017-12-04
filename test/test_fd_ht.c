#include <stdlib.h>

#include "fd_ht.h"
#include "unity.h"

typedef struct key_t {
  int k;
} key_t;

typedef struct value_t {
  int v;
} value_t;

int cmp_key(void* x, void* y) {
  key_t* x_ = (key_t*)x;
  key_t* y_ = (key_t*)y;
  if (x_->k < y_->k) {
    return -1;
  }
  if (x_->k > y_->k) {
    return 1;
  }
  return 0;
}

int hash_key(void* x) { return ((key_t*)x)->k; }

void test_init_and_creation(void) {
  fd_ht_t ht;
  TEST_ASSERT(FD_OK == fd_ht_init(&ht, cmp_key, hash_key, 7));
  TEST_ASSERT(FD_OK == fd_ht_destroy(&ht));
}

void test_put(void) {
  fd_ht_t ht;
  TEST_ASSERT(FD_OK == fd_ht_init(&ht, cmp_key, hash_key, 7));
  key_t k = {1};
  value_t v = {2};
  TEST_ASSERT(FD_OK == fd_ht_put(&ht, &k, &v));
  TEST_ASSERT(FD_OK == fd_ht_put(&ht, &k, &v));
  TEST_ASSERT(FD_OK == fd_ht_destroy(&ht));
}

void test_get(void) {
  fd_ht_t ht;
  TEST_ASSERT(FD_OK == fd_ht_init(&ht, cmp_key, hash_key, 7));
  key_t k = {1};
  value_t v = {2};
  TEST_ASSERT(FD_OK == fd_ht_put(&ht, &k, &v));
  void* v_out = NULL;
  TEST_ASSERT(FD_OK == fd_ht_get(&ht, &k, &v_out));
  TEST_ASSERT_NOT_NULL(v_out);
  v_out = NULL;
  k.k = 2;
  TEST_ASSERT(FD_NOT_FOUND == fd_ht_get(&ht, &k, &v_out));
  TEST_ASSERT_NULL(v_out);
  TEST_ASSERT(FD_OK == fd_ht_destroy(&ht));
}

void test_remove(void) {
  fd_ht_t ht;
  TEST_ASSERT(FD_OK == fd_ht_init(&ht, cmp_key, hash_key, 7));
  key_t k = {1};
  void* v_out = NULL;
  TEST_ASSERT(FD_NOT_FOUND == fd_ht_remove(&ht, &k, &v_out));
  TEST_ASSERT_NULL(v_out);
  value_t v = {2};
  fd_ht_put(&ht, &k, &v);
  TEST_ASSERT(FD_OK == fd_ht_remove(&ht, &k, &v_out));
  TEST_ASSERT_NOT_NULL(v_out);
  TEST_ASSERT(2 == ((value_t*)v_out)->v);
  key_t k2 = {8}; // maps to same bucket as k
  value_t v2 = { 3} ;
  TEST_ASSERT(FD_NOT_FOUND == fd_ht_get(&ht, &k, &v_out));
  fd_ht_put(&ht, &k, &v);
  fd_ht_put(&ht, &k2, &v2);
  key_t k_not_there = { 15 }; // maps to same bucket as k + k2
  TEST_ASSERT(FD_NOT_FOUND == fd_ht_get(&ht, &k_not_there, &v_out));
  TEST_ASSERT(FD_OK == fd_ht_remove(&ht, &k, &v_out));
  TEST_ASSERT_NOT_NULL(v_out);
  TEST_ASSERT(FD_OK == fd_ht_remove(&ht, &k2, &v_out));
  TEST_ASSERT_NOT_NULL(v_out);
  fd_ht_destroy(&ht);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_init_and_creation);
  RUN_TEST(test_put);
  RUN_TEST(test_get);
  RUN_TEST(test_remove);
  return UNITY_END();
}
