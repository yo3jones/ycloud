#ifndef YMICROSERVICE_INCLUDE_SERVICE_H_
#define YMICROSERVICE_INCLUDE_SERVICE_H_
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <vector>
#include "capabilities.h"
#include "capability.h"
#include "startable.h"

namespace ymicroservice {

using std::string;

class Service : public Capabilities {
#define GET_KEY(C) string(typeid(C).name())

 public:
  Service();
  ~Service();

  template <class C>
  Service& addCapability(C* capability) {
    capabilities.insert_or_assign(GET_KEY(C), capability);

    orderedCapabilities.push_back(capability);

    if (auto* startable = dynamic_cast<Startable*>(capability)) {
      startableCapabilities.push_back(startable);
    }
    return *this;
  }

  template <class C>
  C* getCapability() const {
    return (C*)capabilities.at(GET_KEY(C));
  }

  void start();

  void stop();

  void waitForStart();

 private:
  std::unordered_map<string, Capability*> capabilities;
  std::vector<Capability*>                orderedCapabilities;
  std::vector<Startable*>                 startableCapabilities;

  void runBeforeStart();
  void runStart();
  void runShutdown();
};

}  // namespace ymicroservice

#endif  // !YMICROSERVICE_INCLUDE_SERVICE_H_
