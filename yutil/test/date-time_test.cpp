#include "../include/yutil.h"
#include "gtest/gtest.h"

TEST(DateTimeTest, toString) {
  yutil::DateTime now;
}

TEST(DateTimeTest, fromISO) {
  yutil::DateTime dt{"2023-01-06T08:02:09.001Z"};
  EXPECT_EQ(dt.toString(), "2023-01-06T08:02:09.001Z");
}

TEST(DateTimeTest, fromDb) {
  yutil::DateTime dt{"2023-01-12 08:38:09.234Z"};
  EXPECT_EQ(dt.toString(), "2023-01-12T08:38:09.234Z");
}

TEST(DateTimeTest, noMills) {
  yutil::DateTime dt{"2023-01-12 08:38:10Z"};
  EXPECT_EQ(dt.toString(), "2023-01-12T08:38:10.000Z");
}

TEST(DateTimeTest, infalid) {
  try {
    yutil::DateTime dt{"this is bad"};
    FAIL() << "expected exception";
  } catch (...) {
  }
}
