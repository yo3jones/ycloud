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

  static Connection* createConnection();
  static Connection* createConnection(ConnectionInfo connInfo);

  static ConnectionInfo defaultConnInfo;
  static ConnectionInfo connInfo;

 private:
  static void cleanupTestDatabase(Connection* conn, const string& database);
  static void cleanupTestDatabase(ConnectionInfo connInfo,
                                  const string&  database);
  static void initTestDatabase(ConnectionInfo connInfo, const string& database);
};

#endif  // YDB_TEST_INCLUDE_POSTGRESQL_TEST_ENVIORNMENT_H_
