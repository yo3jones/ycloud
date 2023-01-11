#ifndef YUTIL_SRC_UUID_H_
#define YUTIL_SRC_UUID_H_
#include <ostream>
#include <string>
#include "boost/uuid/uuid.hpp"
#include "boost/uuid/uuid_generators.hpp"
#include "boost/uuid/uuid_io.hpp"

namespace yutil {

using std::string;

class UUID {
 public:
  UUID();
  UUID(const string& uuidString);

  string toString() const;

 private:
  boost::uuids::uuid uuid;

  friend std::ostream& operator<<(std::ostream& os, const UUID& uuid);
};

std::ostream& operator<<(std::ostream& os, const UUID& uuid);

void createUuid();

}  // namespace yutil

#endif  // !YUTIL_SRC_UUID_H_
