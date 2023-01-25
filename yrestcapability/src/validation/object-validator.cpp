#include "./object-validator.h"
#include "./validation-constraint.h"

namespace ymicroservice {
namespace validation {

ObjectValidator::ObjectValidator(Constraint constraint)
    : Validator(constraint, OBJECT, {crow::json::type::Object}),
      map(new std::unordered_map<string, Validator*>()) {}

ObjectValidator::ObjectValidator() : ObjectValidator(DEFAULT) {}

ObjectValidator::~ObjectValidator() {
  if (map == nullptr) {
    return;
  }
  for (auto [_, validator] : *map) {
    delete validator;
  }
  delete map;
}

ObjectValidator* ObjectValidator::field(string key, Validator* validator) {
  map->insert_or_assign(key, validator);
  return this;
}

bool ObjectValidator::validate(ValidationResult*         result,
                               const vector<string>&     path,
                               const crow::json::rvalue& value) const {
  if (Validator::validate(result, path, value)) {
    return true;
  }

  for (auto [childKey, childValidator] : *map) {
    validateChild(result, path, value, childKey, childValidator);
  }

  if (!isStrict(constraint)) {
    return false;
  }

  for (auto childValue : value) {
    if (map->contains(childValue.key())) {
      continue;
    }
    vector<string> childPath = {path};
    childPath.emplace_back(childValue.key());
    result->valid = false;
    result->entries.emplace_back(OBJECT, ValidationReason::INVALID_KEY,
                                 childPath);
  }

  return false;
}

void ObjectValidator::validateChild(ValidationResult*         result,
                                    const vector<string>&     parentPath,
                                    const crow::json::rvalue& parentValue,
                                    string                    childKey,
                                    Validator* childValidator) const {
  vector<string> childPath = {parentPath};
  childPath.emplace_back(childKey);

  if (isRequired(childValidator->getConstraint() &&
                 !parentValue.has(childKey))) {
    result->valid = false;
    result->entries.emplace_back(OBJECT, ValidationReason::REQIRED, childPath);
    return;
  }

  if (!parentValue.has(childKey)) {
    return;
  }

  childValidator->validate(result, childPath, parentValue[childKey]);
}

}  // namespace validation
}  // namespace ymicroservice
