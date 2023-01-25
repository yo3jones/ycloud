#include "./validation-entry.h"

namespace ymicroservice {
namespace validation {

ValidationEntry::ValidationEntry(ValueType valueType, ValidationReason reason)
    : valueType(valueType), reason(reason), path() {}

ValidationEntry::ValidationEntry(ValueType             valueType,
                                 ValidationReason      reason,
                                 const vector<string>& path)
    : valueType(valueType), reason(reason), path(path) {}

ValueType ValidationEntry::getValueType() const {
  return valueType;
}

ValidationReason ValidationEntry::getReason() const {
  return reason;
}

string ValidationEntry::getPath() const {
  string pathString{""};
  bool   first = true;

  for (auto part : path) {
    if (!first) {
      pathString += ".";
    }
    pathString += part;
    first = false;
  }
  return pathString;
}

}  // namespace validation
}  // namespace ymicroservice
