#include <gtest/gtest.h>
#include "./include/postgresql-test-enviornment.h"

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  testing::AddGlobalTestEnvironment(new PostgresqlTestEnvironment);

  return RUN_ALL_TESTS();
}
