#include "./object-schema.h"

namespace yutil {
namespace schema {

ObjectSchema::ObjectSchema(Constraint constraint,
                           initializer_list<pair<const string, Schema*>> il)
    : Schema(OBJECT, constraint), fields(il) {}

ObjectSchema::ObjectSchema(initializer_list<pair<const string, Schema*>> il)
    : ObjectSchema(DEFALT, il) {}

ObjectSchema::~ObjectSchema() {
  for (auto [_, field] : fields) {
    delete field;
  }
}

bool ObjectSchema::contains(string key) const {
  return fields.contains(key);
}

Schema& ObjectSchema::at(string key) const {
  return *fields.at(key);
}

Schema& ObjectSchema::operator[](string key) const {
  return at(key);
}

unordered_map<string, Schema*>::const_iterator ObjectSchema::begin() {
  return fields.begin();
}

unordered_map<string, Schema*>::const_iterator ObjectSchema::end() {
  return fields.end();
}

}  // namespace schema
}  // namespace yutil
