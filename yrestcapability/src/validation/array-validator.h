#ifndef YRESTCAPABILITY_SRC_VALIDATION_ARRAY_VALIDATOR_H_
#define YRESTCAPABILITY_SRC_VALIDATION_ARRAY_VALIDATOR_H_
#include <string>
#include <vector>
#include "./crow.h"
#include "./validator.h"

namespace ymicroservice {
namespace validation {

using std::string;
using std::vector;

class ArrayValidator : public Validator {
 public:
  ArrayValidator(Constraint constraint, Validator* elementsValidator);
  explicit ArrayValidator(Validator* elementsValidator);
  ~ArrayValidator();

  bool validate(ValidationResult*         result,
                const vector<string>&     path,
                const crow::json::rvalue& value) const override;

 private:
  Validator* elementsValidator;
};

}  // namespace validation
}  // namespace ymicroservice

#endif  // !YRESTCAPABILITY_SRC_VALIDATION_ARRAY_VALIDATOR_H_
