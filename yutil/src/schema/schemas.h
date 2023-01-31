#ifndef YUTIL_SRC_SCHEMA_SCHEMAS_H_
#define YUTIL_SRC_SCHEMA_SCHEMAS_H_
#include <initializer_list>
#include <utility>
#include "./array-schema.h"
#include "./object-schema.h"
#include "./schema.h"

namespace yutil {
namespace schema {

using std::initializer_list;
using std::pair;

ObjectSchema* Object(Constraint                                    constraint,
                     initializer_list<pair<const string, Schema*>> il);
ObjectSchema* Object(initializer_list<pair<const string, Schema*>> il);
ArraySchema*  Array(Constraint constraint, Schema* elementsSchema);
ArraySchema*  Array(Schema* elementsSchema);
Schema*       String(Constraint constraint = DEFALT);
Schema*       Int(Constraint constraint = DEFALT);
Schema*       Float(Constraint constraint = DEFALT);
Schema*       Bool(Constraint constraint = DEFALT);
Schema*       Id(Constraint constraint = DEFALT);
Schema*       Date(Constraint constraint = DEFALT);
Schema*       DateTime(Constraint constraint = DEFALT);

}  // namespace schema
}  // namespace yutil

#endif  // !YUTIL_SRC_SCHEMA_SCHEMAS_H_
