#ifndef YRESTCAPABILITY_SRC_VALIDATION_VALUE_VALIDATOR_H_
#define YRESTCAPABILITY_SRC_VALIDATION_VALUE_VALIDATOR_H_
#include <optional>
#include "./crow.h"
#include "./validation-entry.h"
#include "./value-type.h"

namespace ymicroservice {
namespace validation {

class ValueValidator {
 public:
  virtual ~ValueValidator() = default;

  virtual std::optional<ValidationReason> isValid(
      ValueType                 valueType,
      const crow::json::rvalue& value) const = 0;
};

}  // namespace validation
}  // namespace ymicroservice

#endif  // !YRESTCAPABILITY_SRC_VALIDATION_VALUE_VALIDATOR_H_
