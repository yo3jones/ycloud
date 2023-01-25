#include <regex>  // NOLINT

#include "./pattern-validator.h"
#include "./validation-entry.h"

namespace ymicroservice {
namespace validation {

PatternValidator::PatternValidator(string pattern) : pattern(pattern) {}

optional<ValidationReason> PatternValidator::isValid(
    ValueType                 valueType,
    const crow::json::rvalue& value) const {
  std::regex r{pattern};

  if (!std::regex_match(string(value.s()), r)) {
    return ValidationReason::INVALID_FORMAT;
  }

  return {};
}

}  // namespace validation
}  // namespace ymicroservice
