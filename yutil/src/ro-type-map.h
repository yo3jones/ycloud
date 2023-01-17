#ifndef YUTIL_SRC_RO_TYPE_MAP_H_
#define YUTIL_SRC_RO_TYPE_MAP_H_
#include "./type-map.h"

namespace yutil {

class ROTypeMap {
 public:
  ROTypeMap(const TypeMap& backingMap);

  template <typename T>
  T* get() const {
    return backingMap.get<T>();
  }

 private:
  const TypeMap& backingMap;
};

}  // namespace yutil

#endif  // !YUTIL_SRC_RO_TYPE_MAP_H_
