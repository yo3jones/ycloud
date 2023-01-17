#ifndef YMICROSERVICE_INCLUDE_CAPABILITY_H_
#define YMICROSERVICE_INCLUDE_CAPABILITY_H_
#include <string>
#include "yutil.h"

namespace ymicroservice {

using std::string;
using yutil::ROTypeMap;

class Capability {
 public:
  virtual ~Capability() = default;

  virtual void beforeStart(const ROTypeMap& capabilities);

  virtual void shutdown();
};

}  // namespace ymicroservice

#endif  // !YMICROSERVICE_INCLUDE_CAPABILITY_H_
