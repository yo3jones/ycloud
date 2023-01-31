#ifndef YUTIL_SRC_SCHEMA_OBJECT_SCHEMA_H_
#define YUTIL_SRC_SCHEMA_OBJECT_SCHEMA_H_
#include <initializer_list>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include "./schema.h"
#include "./value-type.h"

namespace yutil {
namespace schema {

using std::initializer_list;
using std::pair;
using std::string;
using std::unordered_map;

class ObjectSchema : public Schema {
 public:
  explicit ObjectSchema(Constraint constraint,
                        initializer_list<pair<const string, Schema*>> il);
  explicit ObjectSchema(initializer_list<pair<const string, Schema*>> il);
  ~ObjectSchema();

  bool contains(string key) const;

  Schema& at(string key) const;

  template <typename T>
  T& atc(string key) const {
    return *dynamic_cast<T*>(fields.at(key));
  }

  Schema& operator[](string key) const;

  unordered_map<string, Schema*>::const_iterator begin();
  unordered_map<string, Schema*>::const_iterator end();

 private:
  unordered_map<string, Schema*> fields;
};

}  // namespace schema
}  // namespace yutil

#endif  // !YUTIL_SRC_SCHEMA_OBJECT_SCHEMA_H_
