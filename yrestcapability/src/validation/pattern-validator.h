#ifndef YRESTCAPABILITY_SRC_VALIDATION_PATTERN_VALIDATOR_H_
#define YRESTCAPABILITY_SRC_VALIDATION_PATTERN_VALIDATOR_H_
#include <optional>
#include <string>
#include "./value-validator.h"

namespace ymicroservice {
namespace validation {

using std::optional;
using std::string;

class PatternValidator : public ValueValidator {
 public:
  explicit PatternValidator(string pattern);

  optional<ValidationReason> isValid(
      ValueType                 valueType,
      const crow::json::rvalue& value) const override;

 private:
  string pattern;
};

}  // namespace validation
}  // namespace ymicroservice

#endif  // !YRESTCAPABILITY_SRC_VALIDATION_PATTERN_VALIDATOR_H_
