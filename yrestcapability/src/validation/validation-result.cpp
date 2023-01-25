#include "./validation-result.h"

namespace ymicroservice {
namespace validation {

ValidationResult::ValidationResult() : valid(true), entries() {}

bool ValidationResult::isValid() const {
  return valid;
}

const vector<ValidationEntry>& ValidationResult::getEntries() const {
  return entries;
}

}  // namespace validation
}  // namespace ymicroservice
