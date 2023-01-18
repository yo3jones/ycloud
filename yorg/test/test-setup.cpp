#include "../src/middleware.h"
#include "../src/service.h"
#include "./microservice-test-environment.h"
#include "./ydb.h"
#include "./yrestcapability.h"
#include "./yutil.h"
#include "gmock/gmock.h"
#include "pqxx/pqxx"

class YOrgTestEnvironment : public ::testing::Environment {
 public:
  void SetUp() override { cleanup(); }

  void TearDown() override { cleanup(); }

  void cleanup() {
    yutil::Env           env;
    ydb::ConnectionInfo  connInfo{env,
                                 ydb::ConnectionInfo::USE_DEFAULT_DATABASE};
    pqxx::connection     conn{connInfo.toURI()};
    pqxx::nontransaction txn{conn};

    try {
      txn.exec("DROP DATABASE " + env.dbDatabase());
    } catch (...) {
    }

    conn.close();
  }
};

int main(int argc, char** argv) {
  ::testing::InitGoogleMock(&argc, argv);

  yutil::Env    env;
  yorg::Service service{env};
  auto&         microservice = service.getService();
  auto*         restCapability =
      microservice.getCapability<ymicroservice::RESTCapability<MIDDLEWARE>>();
  auto& app = restCapability->getApp();

  app.loglevel(crow::LogLevel::Error);

  testing::AddGlobalTestEnvironment(new YOrgTestEnvironment());
  testing::AddGlobalTestEnvironment(
      new ymicroservice::MicroserviceTestEnvironment(microservice));

  return RUN_ALL_TESTS();
}
