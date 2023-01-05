#ifndef YUTIL_SRC_SEMAPHORE_H_
#define YUTIL_SRC_SEMAPHORE_H_
#include <condition_variable>  // NOLINT
#include <mutex>               // NOLINT

namespace yutil {

class Semaphore {
 public:
  Semaphore();
  explicit Semaphore(int desired);

  void aquire();
  void release();

 private:
  std::mutex              lock;
  std::mutex              countLock;
  std::mutex              aquireLock;
  std::condition_variable condition;
  int                     count;
};

}  // namespace yutil

#endif  // !YUTIL_SRC_SEMAPHORE_H_
