#include "./array-schema.h"

namespace yutil {
namespace schema {

ArraySchema::ArraySchema(Constraint constraint, Schema* elementsSchema)
    : Schema(ARRAY, constraint), elementsSchema(elementsSchema) {}

ArraySchema::ArraySchema(Schema* elementsSchema)
    : ArraySchema(DEFALT, elementsSchema) {}

ArraySchema::~ArraySchema() {
  delete elementsSchema;
}

Schema& ArraySchema::getElementsSchema() const {
  return *elementsSchema;
}

}  // namespace schema
}  // namespace yutil
