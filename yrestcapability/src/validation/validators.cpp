#include "./validators.h"
#include "./value-type.h"
#include "pattern-validator.h"

namespace ymicroservice {
namespace validation {

ObjectValidator* Object(Constraint constraint) {
  return new ObjectValidator(constraint);
}

Validator* String(Constraint constraint, ValueValidator* valueValidator) {
  return new Validator(constraint, STRING, {crow::json::type::String},
                       valueValidator);
}

Validator* String(ValueValidator* valueValidator) {
  return String(DEFAULT, valueValidator);
}

ArrayValidator* Array(Constraint constraint, Validator* validator) {
  return new ArrayValidator{constraint, validator};
}

ArrayValidator* Array(Validator* validator) {
  return new ArrayValidator{DEFAULT, validator};
}

NumberValidator* Int(Constraint constraint, ValueValidator* valueValidator) {
  return new NumberValidator(constraint, INT, valueValidator);
}

NumberValidator* Int(ValueValidator* valueValidator) {
  return Int(DEFAULT, valueValidator);
}

NumberValidator* Float(Constraint constraint, ValueValidator* valueValidator) {
  return new NumberValidator(constraint, FLOAT, valueValidator);
}

NumberValidator* Float(ValueValidator* valueValidator) {
  return Float(DEFAULT, valueValidator);
}

Validator* Bool(Constraint constraint) {
  return new Validator(constraint, BOOL,
                       {crow::json::type::True, crow::json::type::False});
}

Validator* Id(Constraint constraint) {
  return new Validator(
      constraint, ID, {crow::json::type::String},
      new PatternValidator("[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-"
                           "fA-F]{4}-[0-9a-fA-F]{12}"));
}

Validator* Date(Constraint constraint) {
  return new Validator(constraint, ID, {crow::json::type::String},
                       new PatternValidator("[0-9]{4}-[0-9]{2}-[0-9]{2}"));
}

Validator* DateTime(Constraint constraint) {
  return new Validator(
      constraint, ID, {crow::json::type::String},
      new PatternValidator("[0-9]{4}-[0-9]{2}-[0-9]{2}T[0-9]{2}:[0-9]{2}:[0-9]{"
                           "2}\\.[0-9]{3}(Z|[+-][0-9]{2}(:[0-9]{2})?)"));
  // "2}\\.[0-9]{3}(Z|[+-][0-9]{2}(:[0-9]{2}))?"));
}

}  // namespace validation
}  // namespace ymicroservice
