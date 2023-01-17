#ifndef YMICROSERVICE_INCLUDE_SERVICE_H_
#define YMICROSERVICE_INCLUDE_SERVICE_H_
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <vector>
#include "capability.h"
#include "startable.h"
#include "yutil.h"

namespace ymicroservice {

using std::string;
using yutil::TypeMap;

class Service {
 public:
  Service();
  ~Service();

  template <class C>
  Service& addCapability(C* capability) {
    capabilities.insert<C>(capability);

    orderedCapabilities.push_back(capability);

    if (auto* startable = dynamic_cast<Startable*>(capability)) {
      startableCapabilities.push_back(startable);
    }
    return *this;
  }

  template <class C>
  C* getCapability() const {
    return capabilities.get<C>();
  }

  void start();

  void stop();

  void waitForStart();

 private:
  TypeMap                  capabilities;
  std::vector<Capability*> orderedCapabilities;
  std::vector<Startable*>  startableCapabilities;

  void runBeforeStart();
  void runStart();
  void runShutdown();
};

}  // namespace ymicroservice

#endif  // !YMICROSERVICE_INCLUDE_SERVICE_H_
