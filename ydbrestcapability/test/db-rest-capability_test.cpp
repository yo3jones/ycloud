#include "./rest-client.h"
#include "./ydb.h"
#include "./yutil.h"
#include "gtest/gtest.h"
#include "pqxx/pqxx"

class DBRESTCapabilityTest : public testing::Test {
  void SetUp() override {
    pqxx::connection conn{ydb::ConnectionInfo(yutil::Env()).toURI()};
    cleanup(conn);

    pqxx::work txn{conn};

    txn.exec("INSERT INTO ydbrestcapability (name) VALUES ('foo')");

    txn.commit();
    conn.close();
  }

  void TearDown() override { cleanup(); }

  void cleanup() {
    pqxx::connection conn{ydb::ConnectionInfo(yutil::Env()).toURI()};
    cleanup(conn);
    conn.close();
  }

  void cleanup(pqxx::connection& conn) {  // NOLINT
    pqxx::work txn{conn};

    txn.exec("TRUNCATE TABLE ydbrestcapability");

    txn.commit();
  }
};

TEST_F(DBRESTCapabilityTest, bar) {
  ymicroservice::RESTClient client{yutil::Env()};

  auto res = client.get("/hello");

  EXPECT_EQ(res["name"].s(), "foo");
}
