#ifndef YRESTCAPABILITY_SRC_VALIDATION_RANGE_VALIDATOR_H_
#define YRESTCAPABILITY_SRC_VALIDATION_RANGE_VALIDATOR_H_
#include <optional>
#include "./validation-entry.h"
#include "./value-type.h"
#include "./value-validator.h"

namespace ymicroservice {
namespace validation {

template <typename T>
class RangeValidator : public ValueValidator {
 public:
  RangeValidator(T from, T to) : from(from), to(to) {}

  std::optional<ValidationReason> isValid(
      ValueType                 valueType,
      const crow::json::rvalue& value) const override {
    T v = valueType == INT ? value.i() : value.d();

    if (v < from) {
      return ValidationReason::OUT_OF_RANGE;
    }
    if (v > to) {
      return ValidationReason::OUT_OF_RANGE;
    }
    return {};
  }

 private:
  T from;
  T to;
};

}  // namespace validation
}  // namespace ymicroservice

#endif  // !YRESTCAPABILITY_SRC_VALIDATION_RANGE_VALIDATOR_H_
