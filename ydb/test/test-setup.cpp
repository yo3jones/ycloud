#include <gtest/gtest.h>
#include "./postgresql-test-enviornment.h"

using ydb::testing::PostgresqlTestEnvironment;

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  testing::AddGlobalTestEnvironment(new PostgresqlTestEnvironment());

  return RUN_ALL_TESTS();
}
