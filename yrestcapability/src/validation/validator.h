#ifndef YRESTCAPABILITY_SRC_VALIDATION_VALIDATOR_H_
#define YRESTCAPABILITY_SRC_VALIDATION_VALIDATOR_H_
#include <string>
#include <vector>
#include "./crow.h"
#include "./validation-constraint.h"
#include "./validation-result.h"
#include "./value-type.h"
#include "./value-validator.h"

namespace ymicroservice {
namespace validation {

using std::string;
using std::vector;

class Validator {
 public:
  Validator(Constraint               constraint,
            ValueType                valueType,
            vector<crow::json::type> crowValueTypes,
            ValueValidator*          valueValidator = nullptr);

  virtual ~Validator();

  virtual Constraint getConstraint() const;

  virtual ValidationResult validate(const crow::json::rvalue& value) const;

  virtual bool validate(ValidationResult*         result,
                        const vector<string>&     path,
                        const crow::json::rvalue& value) const;

 protected:
  Constraint               constraint;
  ValueType                valueType;
  vector<crow::json::type> crowValueTypes;
  ValueValidator*          valueValidator;
};

}  // namespace validation
}  // namespace ymicroservice

#endif  // !YRESTCAPABILITY_SRC_VALIDATION_VALIDATOR_H_
