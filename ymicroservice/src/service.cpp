#include "../include/service.h"
#include <future>
#include <iostream>
#include <vector>
#include "startable.h"

namespace ymicroservice {

Service::Service() : capabilities(), orderedCapabilities() {}

Service::~Service() {
  for (auto [_, capability] : capabilities) {
    delete capability;
  }
}

void Service::start() {
  runBeforeStart();

  runStart();

  runShutdown();
}

void Service::runBeforeStart() {
  for (auto capability : orderedCapabilities) {
    capability->beforeStart(*this);
  }
}

void Service::runStart() {
  std::vector<std::future<void>> futures;

  // use a thread per start call
  for (auto* capability : orderedCapabilities) {
    auto* startable = dynamic_cast<Startable*>(capability);
    if (startable == nullptr) {
      continue;
    }

    auto future = std::async(&Startable::start, startable);
    futures.push_back(std::move(future));
  }

  // wait for startables to complete
  for (int i = 0; i < futures.size(); i++) {
    futures[i].wait();
  }
}

void Service::runShutdown() {
  for (auto capability : orderedCapabilities) {
    capability->shutdown();
  }
}

}  // namespace ymicroservice
