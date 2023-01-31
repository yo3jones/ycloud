#include "./schema.h"

namespace yutil {
namespace schema {

Schema::Schema(ValueType valueType, Constraint constraint)
    : valueType(valueType), constraint(constraint) {}

Schema::Schema(ValueType valueType) : Schema(valueType, DEFALT) {}

ValueType Schema::getType() const {
  return valueType;
}

Constraint Schema::getConstraint() const {
  return constraint;
}

bool Schema::isRequired() const {
  return yutil::schema::isRequired(constraint);
}

bool Schema::isOptional() const {
  return yutil::schema::isOptional(constraint);
}

bool Schema::isLenient() const {
  return yutil::schema::isLenient(constraint);
}

bool Schema::isStrict() const {
  return yutil::schema::isStrict(constraint);
}

bool Schema::isNullable() const {
  return yutil::schema::isNullable(constraint);
}

bool Schema::isNotNullable() const {
  return yutil::schema::isNotNullable(constraint);
}

}  // namespace schema
}  // namespace yutil
