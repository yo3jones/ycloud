#include "./schemas.h"
#include "array-schema.h"
#include "object-schema.h"

namespace yutil {
namespace schema {

ObjectSchema* Object(Constraint                                    constraint,
                     initializer_list<pair<const string, Schema*>> il) {
  return new ObjectSchema(constraint, il);
}

ObjectSchema* Object(initializer_list<pair<const string, Schema*>> il) {
  return new ObjectSchema(DEFALT, il);
}

ArraySchema* Array(Constraint constraint, Schema* elementsSchema) {
  return new ArraySchema(constraint, elementsSchema);
}

ArraySchema* Array(Schema* elementsSchema) {
  return new ArraySchema(DEFALT, elementsSchema);
}

Schema* String(Constraint constraint) {
  return new Schema(STRING, constraint);
}

Schema* Int(Constraint constraint) {
  return new Schema(INT, constraint);
}

Schema* Float(Constraint constraint) {
  return new Schema(FLOAT, constraint);
}

Schema* Bool(Constraint constraint) {
  return new Schema(BOOL, constraint);
}

Schema* Id(Constraint constraint) {
  return new Schema(ID, constraint);
}

Schema* Date(Constraint constraint) {
  return new Schema(DATE, constraint);
}

Schema* DateTime(Constraint constraint) {
  return new Schema(DATETIME, constraint);
}

}  // namespace schema
}  // namespace yutil
