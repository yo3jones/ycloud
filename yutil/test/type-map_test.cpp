#include <string>
#include "gtest/gtest.h"
#include "yutil.h"

class BaseTestClass {
 public:
  std::string value;

  BaseTestClass(std::string value) : value(value) {}
};

class TestClassOne : public BaseTestClass {
 public:
  TestClassOne(std::string value) : BaseTestClass(value) {}
};

class TestClassTwo : public BaseTestClass {
 public:
  TestClassTwo(std::string value) : BaseTestClass(value) {}
};

TEST(TypeMapTest, insertGet) {
  yutil::TypeMap typeMap;
  TestClassOne   testClassOne("foo");
  TestClassTwo   testClassTwo("bar");

  typeMap.insert(&testClassOne);
  typeMap.insert(&testClassTwo);

  EXPECT_EQ(typeMap.get<TestClassOne>()->value, "foo");
  EXPECT_EQ(typeMap.get<TestClassTwo>()->value, "bar");
}

TEST(TypeMapTest, roTypeMap) {
  yutil::TypeMap typeMap;
  TestClassOne   testClassOne("foo");
  TestClassTwo   testClassTwo("bar");

  typeMap.insert(&testClassOne);
  typeMap.insert(&testClassTwo);

  yutil::ROTypeMap roMap{typeMap};

  EXPECT_EQ(roMap.get<TestClassOne>()->value, "foo");
  EXPECT_EQ(roMap.get<TestClassTwo>()->value, "bar");
}
