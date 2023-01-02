#include <gtest/gtest.h>
#include <string>
#include "../include/result.h"
#include "./include/postgresql-test-enviornment.h"

using ydb::Result;

class PostgresqlTest : public ::testing::Test {
 public:
  void SetUp() override {
    conn1 = PostgresqlTestEnvironment::createConnection();
    conn1->exec("DROP TABLE IF EXISTS test_result");

    conn1->exec(
        "CREATE TABLE test_result ("
        "  first_name varchar(50), "
        "  last_name varchar(50), "
        "  birth_year smallint"
        ")");

    conn1->exec(
        "INSERT INTO test_result "
        "  (first_name, last_name, birth_year) "
        "VALUES "
        "  ('Chris', 'Jones', 1982), "
        "  ('Emmie', 'Jones', 2018), "
        "  ('Mark', 'Stone', null)");

    conn2 = PostgresqlTestEnvironment::createConnection();
  }
  void TearDown() override {
    conn1->exec("DROP TABLE IF EXISTS test_result");
    delete conn1;

    conn2->disconnect();
    delete conn2;
  }

  ydb::Connection* conn1;
  ydb::Connection* conn2;
};

TEST_F(PostgresqlTest, getRowCount) {
  Result result =
      conn1->exec("SELECT * FROM test_result ORDER BY last_name, first_name");
  EXPECT_EQ(result.getRowCount(), 3);
}

TEST_F(PostgresqlTest, referenceAtIndex) {
  Result result = conn1->exec(
      "SELECT first_name, last_name "
      "FROM test_result "
      "ORDER BY last_name, first_name");

  ydb::Row row = result[2];
  EXPECT_EQ(row[0].asString(), "Mark");
  EXPECT_EQ(row[1].asString(), "Stone");
}

TEST_F(PostgresqlTest, referenceAtColumn) {
  Result result = conn1->exec(
      "SELECT first_name, last_name "
      "FROM test_result "
      "ORDER BY last_name, first_name");

  ydb::Row row = result[2];
  EXPECT_EQ(row["last_name"].asString(), "Stone");
  EXPECT_EQ(row["first_name"].asString(), "Mark");
}

TEST_F(PostgresqlTest, selectInt) {
  Result result = conn1->exec(
      "SELECT * "
      "FROM test_result "
      "ORDER BY last_name, first_name");

  ydb::Row row = result[0];
  EXPECT_EQ(row["birth_year"].asInt(), 1982);
}

TEST_F(PostgresqlTest, selectValueIsNull) {
  Result result = conn1->exec(
      "SELECT * "
      "FROM test_result "
      "ORDER BY last_name, first_name");

  ydb::Row chrisRow = result[0];
  ydb::Row markRow  = result[2];
  EXPECT_EQ(chrisRow["birth_year"].isNull(), false);
  EXPECT_EQ(markRow["birth_year"].isNull(), true);
}

TEST_F(PostgresqlTest, commitTransaction) {
  ydb::Transaction txn = conn1->createTransaction();

  conn1->exec(txn, "INSERT INTO test_result (last_name) VALUES ('Foo')");

  Result inTxnResult =
      conn1->exec(txn, "SELECT * FROM test_result WHERE last_name='Foo'");
  Result outTxnResult =
      conn2->exec("SELECT * FROM test_result WHERE last_name='Foo'");

  txn.commit();

  Result afterTxnResult =
      conn1->exec("SELECT * FROM test_result WHERE last_name='Foo'");

  EXPECT_EQ(inTxnResult.getRowCount(), 1);
  EXPECT_EQ(outTxnResult.getRowCount(), 0);
  EXPECT_EQ(afterTxnResult.getRowCount(), 1);
}

TEST_F(PostgresqlTest, abordTransaction) {
  ydb::Transaction txn = conn1->createTransaction();

  conn1->exec(txn, "INSERT INTO test_result (last_name) VALUES ('Foo')");

  Result inTxnResult =
      conn1->exec(txn, "SELECT * FROM test_result WHERE last_name='Foo'");

  txn.abort();

  Result afterTxnResult =
      conn1->exec("SELECT * FROM test_result WHERE last_name='Foo'");

  EXPECT_EQ(inTxnResult.getRowCount(), 1);
  EXPECT_EQ(afterTxnResult.getRowCount(), 0);
}
