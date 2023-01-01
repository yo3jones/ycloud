#ifndef YDB_TEST_INCLUDE_POSTGRESQL_TEST_ENVIORNMENT_H_
#define YDB_TEST_INCLUDE_POSTGRESQL_TEST_ENVIORNMENT_H_
#include "../../include/connection-info.h"
#include "../../include/connection.h"
#include "gtest/gtest.h"
#include "string"

using ydb::Connection;
using ydb::ConnectionInfo;

class PostgresqlTestEnvironment : public ::testing::Environment {
 public:
  PostgresqlTestEnvironment();
  ~PostgresqlTestEnvironment() override;

  void SetUp() override;
  void TearDown() override;

  static Connection* conn;
  ConnectionInfo     defaultConnInfo;
  ConnectionInfo     connInfo;

 private:
  void cleanupTestDatabase(Connection* conn, const string& database);
  void cleanupTestDatabase(ConnectionInfo connInfo, const string& database);
  void initTestDatabase(ConnectionInfo connInfo, const string& database);
};

#endif  // YDB_TEST_INCLUDE_POSTGRESQL_TEST_ENVIORNMENT_H_
