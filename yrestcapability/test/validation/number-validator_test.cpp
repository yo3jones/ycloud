#include "./crow.h"
#include "./yrestcapability.h"
#include "gtest/gtest.h"

using ymicroservice::validation::Float;
using ymicroservice::validation::FLOAT;
using ymicroservice::validation::INT;
using ymicroservice::validation::Int;
using ymicroservice::validation::RangeValidator;
using ymicroservice::validation::ValidationReason;
using ymicroservice::validation::Validator;

TEST(NumberValidatorTest, validInt) {
  auto       rvalue    = crow::json::load(R"json(1234)json");
  Validator* validator = Int();

  auto r = validator->validate(rvalue);

  EXPECT_EQ(r.isValid(), true);

  delete validator;
}

TEST(NumberValidatorTest, validFloat) {
  auto       rvalue    = crow::json::load(R"json(12.34)json");
  Validator* validator = Float();

  auto r = validator->validate(rvalue);

  EXPECT_EQ(r.isValid(), true);

  delete validator;
}

TEST(NumberValidatorTest, notValidIntWithFloat) {
  auto       rvalue    = crow::json::load(R"json(12.34)json");
  Validator* validator = Int();

  auto r = validator->validate(rvalue);

  EXPECT_EQ(r.isValid(), false);
  EXPECT_EQ(r.getEntries().size(), 1);
  EXPECT_EQ(r.getEntries()[0].getValueType(), INT);
  EXPECT_EQ(r.getEntries()[0].getReason(), ValidationReason::INVALID_TYPE);
  EXPECT_EQ(r.getEntries()[0].getPath(), "");

  delete validator;
}

TEST(NumberValidatorTest, notValidFloatWithInt) {
  auto       rvalue    = crow::json::load(R"json(1234)json");
  Validator* validator = Float();

  auto r = validator->validate(rvalue);

  EXPECT_EQ(r.isValid(), false);
  EXPECT_EQ(r.getEntries().size(), 1);
  EXPECT_EQ(r.getEntries()[0].getValueType(), FLOAT);
  EXPECT_EQ(r.getEntries()[0].getReason(), ValidationReason::INVALID_TYPE);
  EXPECT_EQ(r.getEntries()[0].getPath(), "");

  delete validator;
}

TEST(NumberValidatorTest, validRange) {
  auto       rvalue    = crow::json::load(R"json(5)json");
  Validator* validator = Int(new RangeValidator<int>(0, 10));

  auto r = validator->validate(rvalue);

  EXPECT_EQ(r.isValid(), true);

  delete validator;
}

TEST(NumberValidatorTest, notValidRange) {
  auto       rvalue    = crow::json::load(R"json(20)json");
  Validator* validator = Int(new RangeValidator<int>(0, 10));

  auto r = validator->validate(rvalue);

  EXPECT_EQ(r.isValid(), false);
  EXPECT_EQ(r.getEntries().size(), 1);
  EXPECT_EQ(r.getEntries()[0].getValueType(), INT);
  EXPECT_EQ(r.getEntries()[0].getReason(), ValidationReason::OUT_OF_RANGE);
  EXPECT_EQ(r.getEntries()[0].getPath(), "");

  delete validator;
}
