#ifndef YRESTCAPABILITY_SRC_VALIDATION_NUMBER_VALIDATOR_H_
#define YRESTCAPABILITY_SRC_VALIDATION_NUMBER_VALIDATOR_H_
#include <string>
#include <vector>
#include "./crow.h"
#include "./validation-constraint.h"
#include "./validator.h"
#include "./value-type.h"
#include "./value-validator.h"

namespace ymicroservice {
namespace validation {

using std::string;
using std::vector;

class NumberValidator : public Validator {
 public:
  NumberValidator(Constraint      constraint,
                  ValueType       valueType,
                  ValueValidator* valueValidator = nullptr);
  NumberValidator(ValueType       valueType,
                  ValueValidator* valueValidator = nullptr);

  bool validate(ValidationResult*         result,
                const vector<string>&     path,
                const crow::json::rvalue& value) const;
};

}  // namespace validation
}  // namespace ymicroservice

#endif  // !YRESTCAPABILITY_SRC_VALIDATION_NUMBER_VALIDATOR_H_
