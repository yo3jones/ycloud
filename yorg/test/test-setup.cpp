#include "../src/migrations.h"
#include "gtest/gtest.h"
#include "ydb-test.h"

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  yorg::migrations::Migrations migrations;
  testing::AddGlobalTestEnvironment(
      new ydb::testing::PostgresqlTestEnvironment(migrations.get()));

  return RUN_ALL_TESTS();
}
