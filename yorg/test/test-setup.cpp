#include "../src/migrations.cpp"
#include "gtest/gtest.h"
#include "ydb-test.h"

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  testing::AddGlobalTestEnvironment(new ydb::testing::PostgresqlTestEnvironment(
      (ydb::Migration**)yorg::migrations::MIGRATIONS,
      sizeof(yorg::migrations::MIGRATIONS) / sizeof(ydb::Migration*)));

  return RUN_ALL_TESTS();
}
