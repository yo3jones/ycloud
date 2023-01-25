#ifndef YRESTCAPABILITY_SRC_VALIDATION_VALIDATORS_H_
#define YRESTCAPABILITY_SRC_VALIDATION_VALIDATORS_H_
#include "./array-validator.h"
#include "./number-validator.h"
#include "./object-validator.h"
#include "./validator.h"
#include "./value-type.h"
#include "./value-validator.h"

namespace ymicroservice {
namespace validation {

ObjectValidator* Object(Constraint constraint = DEFAULT);

ArrayValidator* Array(Constraint constraint, Validator* validator);

ArrayValidator* Array(Validator* validator);

Validator* String(Constraint      constraint,
                  ValueValidator* valueValidator = nullptr);

Validator* String(ValueValidator* valueValidator = nullptr);

NumberValidator* Int(Constraint      constraint,
                     ValueValidator* valueValidator = nullptr);

NumberValidator* Int(ValueValidator* valueValidator = nullptr);

NumberValidator* Float(Constraint      constraint,
                       ValueValidator* valueValidator = nullptr);

NumberValidator* Float(ValueValidator* valueValidator = nullptr);

Validator* Bool(Constraint constraint = DEFAULT);

Validator* Id(Constraint constraint = DEFAULT);

Validator* Date(Constraint constraint = DEFAULT);

Validator* DateTime(Constraint constraint = DEFAULT);

}  // namespace validation
}  // namespace ymicroservice

#endif  // !YRESTCAPABILITY_SRC_VALIDATION_VALIDATORS_H_
