#include "./crow.h"
#include "./microservice-test-environment.h"
#include "./rest-capability.h"
#include "./ymicroservice.h"
#include "./yutil.h"
#include "gtest/gtest.h"

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  ymicroservice::Service service;
  auto* restCapability = new ymicroservice::RESTCapability<>(yutil::Env());
  service.addCapability(restCapability);

  auto& app = restCapability->getApp();
  app.loglevel(crow::LogLevel::ERROR);
  CROW_ROUTE(app, "/hello")([]() { return R"json({"hello":"world"})json"; });

  testing::AddGlobalTestEnvironment(
      new ymicroservice::MicroserviceTestEnvironment(service));

  return RUN_ALL_TESTS();
}
