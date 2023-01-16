#ifndef YMICROSERVICE_TEST_INCLUDE_MICROSERVICE_TEST_ENVIRONMENT_H_
#define YMICROSERVICE_TEST_INCLUDE_MICROSERVICE_TEST_ENVIRONMENT_H_
#include <future>
#include <semaphore>
#include "gtest/gtest.h"
#include "service.h"

namespace ymicroservice {

class MicroserviceTestEnvironment : public ::testing::Environment {
 public:
  MicroserviceTestEnvironment(Service& service);

  void SetUp() override;
  void TearDown() override;

 private:
  Service&          service;
  std::future<void> future;
};

}  // namespace ymicroservice

#endif  // !YMICROSERVICE_TEST_INCLUDE_MICROSERVICE_TEST_ENVIRONMENT_H_
