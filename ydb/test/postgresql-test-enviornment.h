#ifndef YDB_TEST_INCLUDE_POSTGRESQL_TEST_ENVIORNMENT_H_
#define YDB_TEST_INCLUDE_POSTGRESQL_TEST_ENVIORNMENT_H_
#include <functional>
#include <vector>
#include "../src/connection-info.h"
#include "../src/migration.h"
#include "../src/migrations-runner.h"
#include "gtest/gtest.h"
#include "pqxx/pqxx"
#include "string"

namespace ydb {
namespace testing {

using std::vector;
using ydb::ConnectionInfo;

class PostgresqlTestEnvironment : public ::testing::Environment {
 public:
  PostgresqlTestEnvironment();
  explicit PostgresqlTestEnvironment(const vector<Migration*>& migrations);
  ~PostgresqlTestEnvironment() override;

  void SetUp() override;
  void TearDown() override;

  static pqxx::connection* createConnection(ConnectionInfo connInfo);
  static pqxx::connection* createConnection();
  static void execInTxn(std::function<void(pqxx::work& txn)> fn);  // NOLINT

  static ConnectionInfo defaultConnInfo;
  static ConnectionInfo connInfo;

 private:
  MigrationsRunner* migrationsRunner;

  static void cleanupTestDatabase(pqxx::connection* conn,
                                  const string&     database);
  static void cleanupTestDatabase(ConnectionInfo connInfo,
                                  const string&  database);
};

}  // namespace testing
}  // namespace ydb

#endif  // YDB_TEST_INCLUDE_POSTGRESQL_TEST_ENVIORNMENT_H_
