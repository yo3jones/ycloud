#include "./number-validator.h"

namespace ymicroservice {
namespace validation {

NumberValidator::NumberValidator(Constraint      constraint,
                                 ValueType       valueType,
                                 ValueValidator* valueValidator)
    : Validator(constraint,
                valueType,
                {crow::json::type::Number},
                valueValidator) {}

NumberValidator::NumberValidator(ValueType       valueType,
                                 ValueValidator* valueValidator)
    : NumberValidator(DEFAULT, valueType, valueValidator) {}

bool NumberValidator::validate(ValidationResult*         result,
                               const vector<string>&     path,
                               const crow::json::rvalue& value) const {
  if (Validator::validate(result, path, value)) {
    return true;
  }

  if (valueType == INT &&
      (value.nt() == crow::json::num_type::Signed_integer ||
       value.nt() == crow::json::num_type::Unsigned_integer)) {
    return false;
  } else if (valueType == INT) {
    result->valid = false;
    result->entries.emplace_back(valueType, ValidationReason::INVALID_TYPE,
                                 path);
    return true;
  }

  if (valueType == FLOAT &&
      value.nt() == crow::json::num_type::Floating_point) {
    return false;
  } else if (valueType == FLOAT) {
    result->valid = false;
    result->entries.emplace_back(valueType, ValidationReason::INVALID_TYPE,
                                 path);
    return true;
  }

  return false;
}

}  // namespace validation
}  // namespace ymicroservice
