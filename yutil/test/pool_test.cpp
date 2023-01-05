#include <pthread.h>
#include <unistd.h>
#include <algorithm>
#include <iterator>
#include <mutex>
#include "../include/yutil.h"
#include "gtest/gtest.h"

namespace poolTest {

#define SLEEP        50
#define MAX_VALUES   10
#define THREAD_COUNT 50

void* doWork(void* p) {
  yutil::Pool<int>* pool = reinterpret_cast<yutil::Pool<int>*>(p);

  int* value = pool->get();
  usleep(SLEEP);

  pool->release(value);

  return NULL;
}

TEST(PoolTest, test) {
  int        nextId = 0;
  std::mutex lock;
  auto       factory = [&nextId, &lock]() -> int* {
    std::lock_guard<std::mutex> l(lock);
    int                         id = nextId;
    nextId++;
    return new int(id);
  };
  auto destroy = [](int* value) { delete value; };

  yutil::Pool<int> pool(MAX_VALUES, factory, destroy);

  pthread_t threads[THREAD_COUNT];

  for (int i = 0; i < THREAD_COUNT; i++) {
    pthread_create(&threads[i], NULL, doWork, reinterpret_cast<void*>(&pool));
  }

  for (int i = 0; i < THREAD_COUNT; i++) {
    void* status;
    pthread_join(threads[i], &status);
  }

  EXPECT_TRUE(pool.availableCount() <= 10);

  int values[MAX_VALUES] = {};
  for (int i = 0; i < MAX_VALUES; i++) {
    int value = *pool.get();
    EXPECT_TRUE(value >= 0 && value < MAX_VALUES);
    values[i] = value;
  }

  std::sort(std::begin(values), std::end(values));
  for (int i = 0; i < MAX_VALUES; i++) {
    EXPECT_EQ(values[i], i);
  }
}

}  // namespace poolTest
