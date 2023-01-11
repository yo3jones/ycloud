#include "../include/yutil.h"
#include "gtest/gtest.h"

TEST(DateTimeTest, randomConstruction) {
  yutil::DateTime now;
}

TEST(DateTimeTest, fromISO) {
  yutil::DateTime dt{"2023-01-06T08:02:09.001Z"};
  EXPECT_EQ(dt.toISO(), "2023-01-06T08:02:09.001Z");
}

TEST(DateTimeTest, fromDb) {
  yutil::DateTime dt{"2023-01-11 19:16:42.919126"};
  EXPECT_EQ(dt.toISO(), "2023-01-11T19:16:42.919Z");
}

TEST(DateTimeTest, noMills) {
  yutil::DateTime dt{"2023-01-12 08:38:10"};
  EXPECT_EQ(dt.toISO(), "2023-01-12T08:38:10.000Z");
}

TEST(DateTimeTest, infalid) {
  try {
    yutil::DateTime dt{"this is bad"};
    FAIL() << "expected exception";
  } catch (...) {
  }
}
