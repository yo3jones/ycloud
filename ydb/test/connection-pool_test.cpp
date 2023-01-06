#include "../include/ydb.h"
#include "gtest/gtest.h"
#include "include/ydb-test.h"

using ydb::testing::PostgresqlTestEnvironment;

TEST(ConnectionPoolTest, test) {
  ydb::ConnectionPool connectionPool(PostgresqlTestEnvironment::connInfo, 10);
  pqxx::connection*   conn = connectionPool.get();
  connectionPool.release(conn);
}
