#ifndef YUTIL_SRC_SCHEMA_SCHEMA_H_
#define YUTIL_SRC_SCHEMA_SCHEMA_H_
#include <iostream>
#include "./constraint.h"
#include "./value-type.h"

namespace yutil {
namespace schema {

class Schema {
 public:
  explicit Schema(ValueType valueType, Constraint constraint);
  explicit Schema(ValueType valueType);
  virtual ~Schema() = default;

  ValueType getType() const;

  Constraint getConstraint() const;

  bool isRequired() const;
  bool isOptional() const;
  bool isLenient() const;
  bool isStrict() const;
  bool isNullable() const;
  bool isNotNullable() const;

 protected:
  const ValueType  valueType;
  const Constraint constraint;
};

}  // namespace schema
}  // namespace yutil

#endif  // !YUTIL_SRC_SCHEMA_SCHEMA_H_
