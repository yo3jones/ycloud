#include "./semaphore.h"

namespace yutil {

Semaphore::Semaphore()
    : lock(), countLock(), aquireLock(), condition(), count(1) {}

Semaphore::Semaphore(int desired)
    : lock(), countLock(), aquireLock(), condition(), count(desired) {}

void Semaphore::aquire() {
  aquireLock.lock();
  countLock.lock();
  count--;
  if (count < 0) {
    countLock.unlock();
    std::unique_lock<std::mutex> l(lock);
    condition.wait(l);
  } else {
    countLock.unlock();
  }
  aquireLock.unlock();
}

void Semaphore::release() {
  countLock.lock();
  count++;
  countLock.unlock();
  condition.notify_one();
}

}  // namespace yutil
