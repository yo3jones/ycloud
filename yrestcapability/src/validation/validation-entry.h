#ifndef YRESTCAPABILITY_SRC_VALIDATION_VALIDATION_ENTRY_H_
#define YRESTCAPABILITY_SRC_VALIDATION_VALIDATION_ENTRY_H_
#include <string>
#include <vector>
#include "./value-type.h"

namespace ymicroservice {
namespace validation {

using std::string;
using std::vector;

enum class ValidationReason {
  REQIRED,
  INVALID_TYPE,
  OUT_OF_RANGE,
  INVALID_FORMAT,
  INVALID_KEY,
  NOT_NULLABLE
};

class ValidationEntry {
 public:
  explicit ValidationEntry(ValueType valueType, ValidationReason reason);
  explicit ValidationEntry(ValueType             valueType,
                           ValidationReason      reason,
                           const vector<string>& path);

  ValueType getValueType() const;

  ValidationReason getReason() const;

  string getPath() const;

 private:
  ValueType        valueType;
  ValidationReason reason;
  vector<string>   path;
};

}  // namespace validation
}  // namespace ymicroservice

#endif  // !YRESTCAPABILITY_SRC_VALIDATION_VALIDATION_ENTRY_H_
