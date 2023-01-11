#include "../include/yutil.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(UuidTest, toString) {
  yutil::UUID uuid;

  EXPECT_THAT(
      uuid.toString(),
      testing::MatchesRegex("^[0-f]{8}-[0-f]{4}-[0-f]{4}-[0-f]{4}-[0-f]{12}$"));
}

TEST(UuidTest, fromString) {
  const auto  uuidString = "9302943d-0729-404b-80fb-575ab2fc91f6";
  yutil::UUID uuid       = yutil::UUID(uuidString);

  EXPECT_EQ(uuid.toString(), uuidString);
}
