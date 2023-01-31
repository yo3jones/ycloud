#ifndef YUTIL_SRC_SCHEMA_ARRAY_SCHEMA_H_
#define YUTIL_SRC_SCHEMA_ARRAY_SCHEMA_H_
#include "./schema.h"

namespace yutil {
namespace schema {

class ArraySchema : public Schema {
 public:
  ArraySchema(Constraint constraint, Schema* elementsSchema);
  ArraySchema(Schema* elementsSchema);
  ~ArraySchema();

  Schema& getElementsSchema() const;

 private:
  Schema* elementsSchema;
};

}  // namespace schema
}  // namespace yutil

#endif  // !YUTIL_SRC_SCHEMA_ARRAY_SCHEMA_H_
