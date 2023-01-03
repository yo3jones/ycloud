#ifndef YDB_TEST_INCLUDE_POSTGRESQL_TEST_ENVIORNMENT_H_
#define YDB_TEST_INCLUDE_POSTGRESQL_TEST_ENVIORNMENT_H_
#include "../src/connection-info.h"
#include "gtest/gtest.h"
#include "pqxx/pqxx"
#include "string"

using ydb::ConnectionInfo;

class PostgresqlTestEnvironment : public ::testing::Environment {
 public:
  PostgresqlTestEnvironment();
  ~PostgresqlTestEnvironment() override;

  void SetUp() override;
  void TearDown() override;

  static pqxx::connection* createConnection(ConnectionInfo connInfo);
  static pqxx::connection* createConnection();

  static ConnectionInfo defaultConnInfo;
  static ConnectionInfo connInfo;

 private:
  static void cleanupTestDatabase(pqxx::connection* conn,
                                  const string&     database);
  static void cleanupTestDatabase(ConnectionInfo connInfo,
                                  const string&  database);
  static void initTestDatabase(ConnectionInfo connInfo, const string& database);
};

#endif  // YDB_TEST_INCLUDE_POSTGRESQL_TEST_ENVIORNMENT_H_
