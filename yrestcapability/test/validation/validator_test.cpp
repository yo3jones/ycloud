#include "./yrestcapability.h"
#include "gtest/gtest.h"

using ymicroservice::validation::DEFAULT;
using ymicroservice::validation::NOT_NULLABLE;
using ymicroservice::validation::NULLABLE;
using ymicroservice::validation::PatternValidator;
using ymicroservice::validation::STRING;
using ymicroservice::validation::ValidationReason;
using ymicroservice::validation::Validator;

TEST(ValidatorTest, valid) {
  crow::json::rvalue value = crow::json::load(R"json("")json");
  Validator          validator(DEFAULT, STRING, {crow::json::type::String});

  auto r = validator.validate(value);

  EXPECT_EQ(r.isValid(), true);
}

TEST(ValidatorTest, validNullable) {
  crow::json::rvalue value = crow::json::load(R"json(null)json");
  Validator          validator(NULLABLE, STRING, {crow::json::type::String});

  auto r = validator.validate(value);

  EXPECT_EQ(r.isValid(), true);
}

TEST(ValidatorTest, notValidNullable) {
  crow::json::rvalue value = crow::json::load(R"json(null)json");
  Validator validator(NOT_NULLABLE, STRING, {crow::json::type::String});

  auto r = validator.validate(value);

  EXPECT_EQ(r.isValid(), false);
  EXPECT_EQ(r.getEntries().size(), 1);
  EXPECT_EQ(r.getEntries()[0].getValueType(), STRING);
  EXPECT_EQ(r.getEntries()[0].getReason(), ValidationReason::NOT_NULLABLE);
}

TEST(ValidatorTest, notValueWrongType) {
  crow::json::rvalue value = crow::json::load(R"json(123)json");
  Validator          validator(DEFAULT, STRING, {crow::json::type::String});

  auto r = validator.validate(value);

  EXPECT_EQ(r.isValid(), false);
  EXPECT_EQ(r.getEntries().size(), 1);
  EXPECT_EQ(r.getEntries()[0].getValueType(), STRING);
  EXPECT_EQ(r.getEntries()[0].getReason(), ValidationReason::INVALID_TYPE);
}

TEST(ValidatorTest, validValueValidator) {
  crow::json::rvalue value = crow::json::load(R"json("12334")json");
  Validator          validator(DEFAULT, STRING, {crow::json::type::String},
                               new PatternValidator("[0-9]+"));

  auto r = validator.validate(value);

  EXPECT_EQ(r.isValid(), true);
}

TEST(ValidatorTest, notValidValueValidator) {
  crow::json::rvalue value = crow::json::load(R"json("abcd")json");
  Validator          validator(DEFAULT, STRING, {crow::json::type::String},
                               new PatternValidator("[0-9]+"));

  auto r = validator.validate(value);

  EXPECT_EQ(r.isValid(), false);
  EXPECT_EQ(r.getEntries().size(), 1);
  EXPECT_EQ(r.getEntries()[0].getValueType(), STRING);
  EXPECT_EQ(r.getEntries()[0].getReason(), ValidationReason::INVALID_FORMAT);
}
