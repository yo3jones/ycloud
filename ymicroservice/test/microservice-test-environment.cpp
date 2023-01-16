#include "include/microservice-test-environment.h"
#include <future>

namespace ymicroservice {

MicroserviceTestEnvironment::MicroserviceTestEnvironment(Service& service)
    : service(service) {}

void MicroserviceTestEnvironment::SetUp() {
  future = std::async(&Service::start, &service);
  service.waitForStart();
}

void MicroserviceTestEnvironment::TearDown() {
  service.stop();
  future.get();
}

}  // namespace ymicroservice
