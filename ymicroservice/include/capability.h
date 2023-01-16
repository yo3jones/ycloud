#ifndef YMICROSERVICE_INCLUDE_CAPABILITY_H_
#define YMICROSERVICE_INCLUDE_CAPABILITY_H_
#include <string>
#include "capabilities.h"

namespace ymicroservice {

using std::string;

class Capability {
 public:
  virtual ~Capability() = default;

  virtual void beforeStart(Capabilities& capabilities);

  virtual void shutdown();
};

}  // namespace ymicroservice

#endif  // !YMICROSERVICE_INCLUDE_CAPABILITY_H_
