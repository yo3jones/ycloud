#include "gtest/gtest.h"
#include "pqxx/pqxx"
#include "ydb-test.h"

TEST(FirstTest, here) {
  auto       conn = ydb::testing::PostgresqlTestEnvironment::createConnection();
  pqxx::work txn{*conn};

  txn.exec("SELECT * FROM task");

  txn.commit();

  conn->close();
  delete conn;
}
