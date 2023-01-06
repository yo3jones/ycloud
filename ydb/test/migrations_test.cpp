#include <string>
#include "../include/ydb.h"
#include "./include/ydb-test.h"
#include "gtest/gtest.h"

using ydb::testing::PostgresqlTestEnvironment;

class MigrationsTest : public ::testing::Test {
 public:
  void SetUp() override {
    connInfo        = PostgresqlTestEnvironment::connInfo;
    defaultConnInfo = PostgresqlTestEnvironment::connInfo;
    cleanupMigrationsTable();
  }
  void TearDown() override { cleanupMigrationsTable(); }

  void cleanupMigrationsTable() {
    pqxx::connection conn{connInfo.toURI()};
    pqxx::work       txn{conn};
    txn.exec("DROP TABLE IF EXISTS test_migrations");
    txn.commit();
    conn.close();
  }

  ydb::ConnectionInfo connInfo;
  ydb::ConnectionInfo defaultConnInfo;
};

class TestMigrationOne : public ydb::Migration {
 public:
  void up(pqxx::work& txn) override {  // NOLINT
    txn.exec("create table foo (name varchar(5))");
  }
  string name() override { return "2023-01-02T14:40 TestMigrationOne"; }
};

class TestMigrationTwo : public ydb::Migration {
 public:
  void up(pqxx::work& txn) override {  // NOLINT
  }
  string name() override { return "2023-01-02T14:55 TestMigrationTwo"; }
};

class TestMigrationError : public ydb::Migration {
 public:
  void up(pqxx::work& txn) override {  // NOLINT
    if (shouldError) {
      txn.exec("something that is now sql");
    }
  }
  string name() override { return "2023-01-02T14:50 TestMigrationTwo"; }

  bool shouldError = true;
};

TEST_F(MigrationsTest, createMigrationsTable) {
  ydb::MigrationsRunner(
      connInfo, defaultConnInfo,
      ydb::MigrationsRunnerOptions().migrationTableName("test_migrations"))
      .run();

  pqxx::connection conn{connInfo.toURI()};
  pqxx::work       txn{conn};

  txn.exec("SELECT * FROM test_migrations");
  txn.commit();

  conn.close();
}

TEST_F(MigrationsTest, migrationStatus) {
  bool caught = false;
  try {
    ydb::MigrationsRunner(
        connInfo, defaultConnInfo,
        ydb::MigrationsRunnerOptions().migrationTableName("test_migrations"))
        .registerMigration(new TestMigrationTwo())
        .registerMigration(new TestMigrationOne())
        .registerMigration(new TestMigrationError())
        .run();
  } catch (...) {
    caught = true;
  }

  EXPECT_EQ(caught, true);

  pqxx::connection conn{connInfo.toURI()};
  pqxx::work       txn{conn};

  pqxx::result res = txn.exec("SELECT * FROM test_migrations ORDER BY name");

  EXPECT_EQ(res.size(), 2);
  EXPECT_EQ(string(res[0]["status"].c_str()), "complete");
  EXPECT_EQ(string(res[1]["status"].c_str()), "error");

  conn.close();
}

TEST_F(MigrationsTest, retry) {
  TestMigrationError*   errorMigration = new TestMigrationError();
  ydb::MigrationsRunner runner(
      connInfo, defaultConnInfo,
      ydb::MigrationsRunnerOptions().migrationTableName("test_migrations"));
  runner.registerMigration(errorMigration);

  try {
    runner.run();
  } catch (...) {
  }

  pqxx::connection conn{connInfo.toURI()};
  pqxx::work       txn{conn};

  pqxx::result res = txn.exec("SELECT * FROM test_migrations ORDER BY name");
  EXPECT_EQ(res.size(), 1);
  EXPECT_EQ(string(res[0]["status"].c_str()), "error");

  errorMigration->shouldError = false;
  runner.run();

  res = txn.exec("SELECT * FROM test_migrations ORDER BY name");
  EXPECT_EQ(res.size(), 1);
  EXPECT_EQ(string(res[0]["status"].c_str()), "complete");

  conn.close();
}
