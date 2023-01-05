#include <pthread.h>
#include <unistd.h>
#include "../include/yutil.h"
#include "gtest/gtest.h"

namespace semaphoreTest {

#define SLEEP             50
#define THREAD_COUNT      10
#define SEMAPHORE_DESIRED 5

void* doWork(void* p) {
  yutil::Semaphore* semaphore = reinterpret_cast<yutil::Semaphore*>(p);
  semaphore->aquire();
  usleep(SLEEP);
  semaphore->release();
  return NULL;
}

TEST(SemaphoreTest, test) {
  pthread_t        threads[THREAD_COUNT];
  yutil::Semaphore semaphore(SEMAPHORE_DESIRED);

  for (int i = 0; i < THREAD_COUNT; i++) {
    pthread_create(&threads[i], NULL, doWork,
                   reinterpret_cast<void*>(&semaphore));
  }

  for (int i = 0; i < THREAD_COUNT; i++) {
    void* status;
    pthread_join(threads[i], &status);
  }
}

}  // namespace semaphoreTest
