#include "./microservice-test-environment.h"
#include "./ydb.h"
#include "./ydbcapability.h"
#include "./ydbrestcapability.h"
#include "./ymicroservice.h"
#include "./yrestcapability.h"
#include "./yutil.h"
#include "gtest/gtest.h"
#include "pqxx/pqxx"

using ymicroservice::DBAccessor;
using ymicroservice::DBCapability;
using ymicroservice::DBMiddleware;
using ymicroservice::DBRESTCapability;
using ymicroservice::MicroserviceTestEnvironment;
using ymicroservice::RESTCapability;
using ymicroservice::Service;

class TestMigration : public ydb::Migration {
  std::string name() override { return "test migration"; }

  void up(pqxx::work& txn) override {
    txn.exec("CREATE TABLE ydbrestcapability (name varchar(255))");
  }
};

#define MIDDLEWARE DBMiddleware

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  yutil::Env             env;
  DBAccessor<MIDDLEWARE> dbAccessor;
  auto*                  restCapability = new RESTCapability<MIDDLEWARE>(env);
  auto*                  dbCapability =
      (new DBCapability(env))->registerMigration(new TestMigration());
  auto* dbRestCapabiliity = new DBRESTCapability<MIDDLEWARE>();

  Service service;
  service.addCapability(restCapability)
      .addCapability(dbCapability)
      .addCapability(dbRestCapabiliity);

  auto& app = restCapability->getApp();
  app.loglevel(crow::LogLevel::ERROR);
  CROW_ROUTE(app, "/hello")
  ([&dbAccessor](const crow::request& req) -> crow::json::wvalue {
    pqxx::connection* conn = dbAccessor.conn(req);
    pqxx::work        txn{*conn};
    auto              res = txn.exec("SELECT * FROM ydbrestcapability");
    return {{"name", res[0]["name"].c_str()}};
  });

  testing::AddGlobalTestEnvironment(new MicroserviceTestEnvironment(service));

  return RUN_ALL_TESTS();
}
