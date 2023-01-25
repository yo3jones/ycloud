#include "./crow.h"
#include "./yrestcapability.h"
#include "crow/json.h"
#include "gtest/gtest.h"

using ymicroservice::validation::Array;
using ymicroservice::validation::ARRAY;
using ymicroservice::validation::NOT_NULLABLE;
using ymicroservice::validation::String;
using ymicroservice::validation::STRING;
using ymicroservice::validation::ValidationReason;
using ymicroservice::validation::Validator;

TEST(ArrayValidatorTest, valid) {
  auto       rvalue    = crow::json::load(R"json(["one", "two"])json");
  Validator* validator = Array(String());

  auto r = validator->validate(rvalue);

  EXPECT_EQ(r.isValid(), true);

  delete validator;
}

TEST(ArrayValidatorTest, invalid) {
  auto       rvalue    = crow::json::load(R"json(null)json");
  Validator* validator = Array(NOT_NULLABLE, String());

  auto r = validator->validate(rvalue);

  EXPECT_EQ(r.isValid(), false);
  EXPECT_EQ(r.getEntries().size(), 1);
  EXPECT_EQ(r.getEntries()[0].getValueType(), ARRAY);
  EXPECT_EQ(r.getEntries()[0].getReason(), ValidationReason::NOT_NULLABLE);
  EXPECT_EQ(r.getEntries()[0].getPath(), "");

  delete validator;
}

TEST(ArrayValidatorTest, invalidElememnt) {
  auto       rvalue    = crow::json::load(R"json(["one", 2])json");
  Validator* validator = Array(String());

  auto r = validator->validate(rvalue);

  EXPECT_EQ(r.isValid(), false);
  EXPECT_EQ(r.getEntries().size(), 1);
  EXPECT_EQ(r.getEntries()[0].getValueType(), STRING);
  EXPECT_EQ(r.getEntries()[0].getReason(), ValidationReason::INVALID_TYPE);
  EXPECT_EQ(r.getEntries()[0].getPath(), "[1]");

  delete validator;
}
