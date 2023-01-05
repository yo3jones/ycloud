#ifndef YUTIL_SRC_POOL_H_
#define YUTIL_SRC_POOL_H_
#include <cstddef>
#include <functional>
#include <iostream>
#include <list>
#include <mutex>
#include <vector>
#include "semaphore.h"

namespace yutil {

template <typename T>
class Pool {
 public:
  Pool(int                     maxValues,
       std::function<T*()>     factory,
       std::function<void(T*)> destroy)
      : semaphore(maxValues),
        maxValues(maxValues),
        factory(factory),
        destroy(destroy),
        available(),
        values() {}

  ~Pool() {
    for (int i = 0; i < values.size(); i++) {
      destroy(values[i]);
    }
  }

  T* get() {
    semaphore.aquire();

    T* value;

    const std::lock_guard<std::mutex> l(lock);

    if (available.empty()) {
      value = factory();
      values.push_back(value);
    } else {
      value = available.front();
      available.pop_front();
    }

    return value;
  }

  void release(T* value) {
    const std::lock_guard<std::mutex> l(lock);
    available.push_back(value);
    semaphore.release();
  }

  size_t availableCount() { return available.size(); }

 private:
  Semaphore               semaphore;
  int                     maxValues;
  std::function<T*()>     factory;
  std::function<void(T*)> destroy;
  std::mutex              lock;
  std::list<T*>           available;
  std::vector<T*>         values;
};

}  // namespace yutil

#endif  // !YUTIL_SRC_POOL_H_
