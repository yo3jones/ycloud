#include "./validation-constraint.h"

namespace ymicroservice {
namespace validation {

bool isRequired(Constraint constraint) {
  return (constraint & REQUIRED) != 0;
}

bool isStrict(Constraint constraint) {
  return (constraint & LENIENT) == 0;
}

bool isNullable(Constraint constraint) {
  return (constraint & NULLABLE) != 0;
}

}  // namespace validation
}  // namespace ymicroservice
