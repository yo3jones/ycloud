#include "gtest/gtest.h"
#include "pqxx/pqxx"
#include "ydb-test.h"

TEST(FirstTest, here) {
  ydb::testing::PostgresqlTestEnvironment::execInTxn(
      [](pqxx::work& txn) { txn.exec("SELECT * FROM task"); });
}
