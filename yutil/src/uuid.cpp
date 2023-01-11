#include "uuid.h"
#include <string>

namespace yutil {

UUID::UUID() : uuid(boost::uuids::random_generator()()) {}

UUID::UUID(const string& uuidString)
    : uuid(boost::uuids::string_generator()(uuidString)) {}

string UUID::toString() const {
  return boost::uuids::to_string(uuid);
}

std::ostream& operator<<(std::ostream& os, const UUID& uuid) {
  return os << uuid.toString();
}

void createUuid() {
  auto u = boost::uuids::random_generator()();
}

}  // namespace yutil
