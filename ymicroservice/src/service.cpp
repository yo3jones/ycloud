#include "../include/service.h"
#include <future>
#include <iostream>
#include <vector>

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

void Service::stop() {
  for (auto startable : startableCapabilities) {
    startable->stop();
  }
}

void Service::waitForStart() {
  for (auto startable : startableCapabilities) {
    startable->waitForStart();
  }
}

void Service::runBeforeStart() {
  for (auto capability : orderedCapabilities) {
    capability->beforeStart(*this);
  }
}

void Service::runStart() {
  std::vector<std::future<void>> futures;

  // use a thread per start call
  for (auto* startable : startableCapabilities) {
    auto future = std::async(&Startable::start, startable);
    futures.push_back(std::move(future));
  }

  // wait for startables to complete
  for (int i = 0; i < futures.size(); i++) {
    // calling get will throw any exceptions thrown
    futures[i].get();
  }
}

void Service::runShutdown() {
  for (auto capability : orderedCapabilities) {
    capability->shutdown();
  }
}

}  // namespace ymicroservice
