#include "./validator.h"

namespace ymicroservice {
namespace validation {

Validator::Validator(Constraint               constraint,
                     ValueType                valueType,
                     vector<crow::json::type> crowValueTypes,
                     ValueValidator*          valueValidator)
    : constraint(constraint),
      valueType(valueType),
      crowValueTypes(crowValueTypes),
      valueValidator(valueValidator) {}

Validator::~Validator() {
  delete valueValidator;
}

Constraint Validator::getConstraint() const {
  return constraint;
}

ValidationResult Validator::validate(const crow::json::rvalue& value) const {
  ValidationResult result;

  validate(&result, {}, value);

  return result;
}

bool Validator::validate(ValidationResult*         result,
                         const vector<string>&     path,
                         const crow::json::rvalue& value) const {
  if (!isNullable(constraint) && value.t() == crow::json::type::Null) {
    result->valid = false;
    result->entries.emplace_back(valueType, ValidationReason::NOT_NULLABLE,
                                 path);
    return true;
  }

  if (value.t() == crow::json::type::Null) {
    return true;
  }

  bool validCrowType = false;
  for (auto crowType : crowValueTypes) {
    if (crowType == value.t()) {
      validCrowType = true;
      break;
    }
  }

  if (!validCrowType) {
    result->valid = false;
    result->entries.emplace_back(valueType, ValidationReason::INVALID_TYPE,
                                 path);
    return true;
  }

  if (valueValidator == nullptr) {
    return false;
  }

  auto valueRes = valueValidator->isValid(valueType, value);
  if (valueRes) {
    result->valid = false;
    result->entries.emplace_back(valueType, valueRes.value(), path);
    return true;
  }

  return false;
}

}  // namespace validation
}  // namespace ymicroservice
