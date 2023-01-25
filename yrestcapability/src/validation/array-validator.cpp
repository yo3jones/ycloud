#include <string>

#include "./array-validator.h"
#include "./crow/json.h"

namespace ymicroservice {
namespace validation {

ArrayValidator::ArrayValidator(Constraint constraint,
                               Validator* elementsValidator)
    : Validator(constraint, ARRAY, {crow::json::type::List}),
      elementsValidator(elementsValidator) {}

ArrayValidator::ArrayValidator(Validator* elementsValidator)
    : ArrayValidator(DEFAULT, elementsValidator) {}

ArrayValidator::~ArrayValidator() {
  delete elementsValidator;
}

bool ArrayValidator::validate(ValidationResult*         result,
                              const vector<string>&     path,
                              const crow::json::rvalue& value) const {
  if (Validator::validate(result, path, value)) {
    return true;
  }

  int i = 0;
  for (auto childValue : value) {
    vector<string> childPath{path};
    childPath.emplace_back("[" + std::to_string(i) + "]");
    i++;

    elementsValidator->validate(result, childPath, childValue);
  }

  return false;
}

}  // namespace validation
}  // namespace ymicroservice
