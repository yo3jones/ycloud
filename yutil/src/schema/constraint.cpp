#include "./constraint.h"

namespace yutil {
namespace schema {

bool isRequired(Constraint constraint) {
  return (REQIRED & constraint) > 0;
}

bool isOptional(Constraint constraint) {
  return !isRequired(constraint);
}

bool isLenient(Constraint constraint) {
  return !isStrict(constraint);
}

bool isStrict(Constraint constraint) {
  return (STRICT & constraint) > 0;
}

bool isNullable(Constraint constraint) {
  return !isNotNullable(constraint);
}

bool isNotNullable(Constraint constraint) {
  return (NOT_NULLABLE & constraint) > 0;
}

}  // namespace schema
}  // namespace yutil
