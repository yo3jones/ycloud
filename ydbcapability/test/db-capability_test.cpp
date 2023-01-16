#include "./ydb.h"
#include "./ydbcapability.h"
#include "./ymicroservice.h"
#include "./yutil.h"
#include "gtest/gtest.h"
#include "pqxx/pqxx"

class TestMigration : public ydb::Migration {
  std::string name() override { return "some migration"; }
  void        up(pqxx::work& txn) override {
    txn.exec("CREATE TABLE foo (name varchar(255))");
  }
};

class DBCapabilityTest : public testing::Test {
  void SetUp() override {
    cleanup();

    ymicroservice::Service()
        .addCapability((new ymicroservice::DBCapability(yutil::Env()))
                           ->registerMigration(new TestMigration()))
        .start();
  }

  void TearDown() override { cleanup(); }

  void cleanup() {
    yutil::Env          env;
    ydb::ConnectionInfo connInfo(env,
                                 ydb::ConnectionInfo::USE_DEFAULT_DATABASE);
    pqxx::connection    conn{connInfo.toURI()};

    pqxx::nontransaction txn{conn};

    txn.exec("DROP DATABASE IF EXISTS " + env.dbDatabase());

    conn.close();
  }
};

TEST_F(DBCapabilityTest, test) {
  pqxx::connection conn{ydb::ConnectionInfo(yutil::Env()).toURI()};
  pqxx::work       txn{conn};

  txn.exec("SELECT * FROM foo");

  conn.close();
}
