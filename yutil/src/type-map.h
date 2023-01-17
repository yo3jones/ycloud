#ifndef YUTIL_SRC_TYPE_MAP_H_
#define YUTIL_SRC_TYPE_MAP_H_
#include <string>
#include <unordered_map>

namespace yutil {

using std::string;

class TypeMap {
#define GET_KEY(T) string(typeid(T).name())

 public:
  template <typename T>
  void insert(T* entry) {
    entries.insert_or_assign(GET_KEY(T), entry);
  }

  template <typename T>
  T* get() const {
    return (T*)entries.at(GET_KEY(T));
  }

 private:
  std::unordered_map<string, void*> entries;
};

}  // namespace yutil

#endif  // !YUTIL_SRC_TYPE_MAP_H_
