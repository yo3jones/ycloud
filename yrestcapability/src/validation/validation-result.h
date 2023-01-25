#ifndef YRESTCAPABILITY_SRC_VALIDATION_VALIDATION_RESULT_H_
#define YRESTCAPABILITY_SRC_VALIDATION_VALIDATION_RESULT_H_
#include <string>
#include <vector>
#include "./validation-entry.h"

namespace ymicroservice {
namespace validation {

using std::string;
using std::vector;

class ValidationResult {
 public:
  ValidationResult();

  bool isValid() const;

  const vector<ValidationEntry>& getEntries() const;

 private:
  bool                    valid;
  vector<ValidationEntry> entries;

  friend class NumberValidator;
  friend class ObjectValidator;
  friend class StringValidator;
  friend class Validator;
};

}  // namespace validation
}  // namespace ymicroservice

#endif  // !YRESTCAPABILITY_SRC_VALIDATION_VALIDATION_RESULT_H_
