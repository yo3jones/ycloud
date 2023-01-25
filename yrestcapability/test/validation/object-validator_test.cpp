#include "./crow.h"
#include "./yrestcapability.h"
#include "crow/json.h"
#include "gtest/gtest.h"

using ymicroservice::validation::Array;
using ymicroservice::validation::Bool;
using ymicroservice::validation::Date;
using ymicroservice::validation::DateTime;
using ymicroservice::validation::Float;
using ymicroservice::validation::Id;
using ymicroservice::validation::Int;
using ymicroservice::validation::LENIENT;
using ymicroservice::validation::NOT_NULLABLE;
using ymicroservice::validation::NULLABLE;
using ymicroservice::validation::OBJECT;
using ymicroservice::validation::Object;
using ymicroservice::validation::ObjectValidator;
using ymicroservice::validation::OPTIONAL;
using ymicroservice::validation::PatternValidator;
using ymicroservice::validation::REQUIRED;
using ymicroservice::validation::STRICT;
using ymicroservice::validation::STRING;
using ymicroservice::validation::String;
using ymicroservice::validation::ValidationReason;
using ymicroservice::validation::Validator;

TEST(ObjectValidatorTest, valid) {
  auto       value     = crow::json::load(R"json({})json");
  Validator* validator = Object();
  auto       result    = validator->validate(value);

  EXPECT_EQ(result.isValid(), true);
}

TEST(ObjectValidatorTest, validNull) {
  auto       value     = crow::json::load(R"json(null)json");
  Validator* validator = Object(NULLABLE);
  auto       result    = validator->validate(value);

  EXPECT_EQ(result.isValid(), true);
}

TEST(ObjectValidatorTest, notValidNull) {
  auto       value     = crow::json::load(R"json(null)json");
  Validator* validator = Object(NOT_NULLABLE);
  auto       result    = validator->validate(value);

  EXPECT_EQ(result.isValid(), false);
  EXPECT_EQ(result.getEntries().size(), 1);
  EXPECT_EQ(result.getEntries()[0].getValueType(), OBJECT);
  EXPECT_EQ(result.getEntries()[0].getReason(), ValidationReason::NOT_NULLABLE);
  EXPECT_EQ(result.getEntries()[0].getPath(), "");
}

TEST(ObjectValidatorTest, notValidNotMap) {
  auto       value     = crow::json::load(R"json("some string")json");
  Validator* validator = Object(NOT_NULLABLE);
  auto       result    = validator->validate(value);

  EXPECT_EQ(result.isValid(), false);
  EXPECT_EQ(result.getEntries().size(), 1);
  EXPECT_EQ(result.getEntries()[0].getValueType(), OBJECT);
  EXPECT_EQ(result.getEntries()[0].getReason(), ValidationReason::INVALID_TYPE);
  EXPECT_EQ(result.getEntries()[0].getPath(), "");
}

TEST(ObjectValidatorTest, allValueTypes) {
  auto value = crow::json::load(R"json(
    {
      "validString": "some string",
      "invalidString": null,
      "validArray": ["some string"],
      "invalidArray": null,
      "validInt": 123,
      "invalidInt": null,
      "validFloat": 12.23,
      "invalidFloat": null,
      "validBool": true,
      "invalidBool": null,
      "validId": "123e4567-e89b-12d3-a456-426614174000",
      "invalidId": "123e456-e9b-12d3-a456-4261417400",
      "validDate": "2023-01-22",
      "invalidDate": "23-01-22",
      "validDateTime1": "2023-01-22T13:31:30.000Z",
      "validDateTime2": "2023-01-22T13:31:30.000-08",
      "validDateTime3": "2023-01-22T13:31:30.000+08",
      "validDateTime4": "2023-01-22T13:31:30.000-08:00",
      "validDateTime5": "2023-01-22T13:31:30.000+08:00",
      "invalidDateTime": "2023-01-22T13:31:30.000"
    }
  )json");

  const ObjectValidator* validator =
      Object()
          ->field("validString", String(NOT_NULLABLE))
          ->field("invalidString", String(NOT_NULLABLE))
          ->field("validArray", Array(NOT_NULLABLE, String()))
          ->field("invalidArray", Array(NOT_NULLABLE, String()))
          ->field("validInt", Int(NOT_NULLABLE))
          ->field("invalidInt", Int(NOT_NULLABLE))
          ->field("validFloat", Float(NOT_NULLABLE))
          ->field("invalidFloat", Float(NOT_NULLABLE))
          ->field("validBool", Bool(NOT_NULLABLE))
          ->field("invalid", Bool(NOT_NULLABLE))
          ->field("validId", Id())
          ->field("invalidId", Id())
          ->field("validDate", Date())
          ->field("invalidDate", Date())
          ->field("validDateTime1", DateTime())
          ->field("validDateTime2", DateTime())
          ->field("validDateTime3", DateTime())
          ->field("validDateTime4", DateTime())
          ->field("validDateTime5", DateTime())
          ->field("invalidDateTime", DateTime());
  auto result = validator->Validator::validate(value);

  EXPECT_EQ(result.isValid(), false);
  EXPECT_EQ(result.getEntries().size(), 8);
}

TEST(ObjectValidatorTest, validFields) {
  auto                   value = crow::json::load(R"json(
    {
      "foo": "foo value",
      "bar": "bar value"
    }
  )json");
  const ObjectValidator* validator =
      Object()->field("foo", String())->field("bar", String());
  auto result = validator->Validator::validate(value);

  EXPECT_EQ(result.isValid(), true);
}

TEST(ObjectValidatorTest, notValidRequiredKey) {
  auto       value = crow::json::load(R"json(
    {
      "foo": "foo value"
    }
  )json");
  Validator* validator =
      Object()->field("foo", String())->field("bar", String(REQUIRED));
  auto result = validator->Validator::validate(value);

  EXPECT_EQ(result.isValid(), false);
  EXPECT_EQ(result.getEntries().size(), 1);
  EXPECT_EQ(result.getEntries()[0].getValueType(), OBJECT);
  EXPECT_EQ(result.getEntries()[0].getReason(), ValidationReason::REQIRED);
  EXPECT_EQ(result.getEntries()[0].getPath(), "bar");
}

TEST(ObjectValidatorTest, validOptionalKey) {
  auto       value = crow::json::load(R"json(
    {
      "foo": "foo value"
    }
  )json");
  Validator* validator =
      Object()->field("foo", String())->field("bar", String(OPTIONAL));
  auto result = validator->Validator::validate(value);

  EXPECT_EQ(result.isValid(), true);
}

TEST(ObjectValidatorTest, notValidFields) {
  auto             value = crow::json::load(R"json(
    {
      "foo": "foo value",
      "bar": 1234
    }
  )json");
  ObjectValidator* validator =
      Object()->field("foo", String())->field("bar", String());
  auto result = validator->Validator::validate(value);

  EXPECT_EQ(result.isValid(), false);
  EXPECT_EQ(result.getEntries().size(), 1);
  EXPECT_EQ(result.getEntries()[0].getValueType(), STRING);
  EXPECT_EQ(result.getEntries()[0].getReason(), ValidationReason::INVALID_TYPE);
  EXPECT_EQ(result.getEntries()[0].getPath(), "bar");
}

TEST(ObjectValidatorTest, validLenient) {
  auto       value     = crow::json::load(R"json(
    {
      "foo": "foo value",
      "extra": "extra"
    }
  )json");
  Validator* validator = Object(LENIENT)->field("foo", String());
  auto       result    = validator->Validator::validate(value);

  EXPECT_EQ(result.isValid(), true);
}

TEST(ObjectValidatorTest, notValidStrict) {
  auto       value     = crow::json::load(R"json(
    {
      "foo": "foo value",
      "extra": "extra"
    }
  )json");
  Validator* validator = Object(STRICT)->field("foo", String());
  auto       result    = validator->Validator::validate(value);

  EXPECT_EQ(result.isValid(), false);
  EXPECT_EQ(result.getEntries().size(), 1);
  EXPECT_EQ(result.getEntries()[0].getValueType(), OBJECT);
  EXPECT_EQ(result.getEntries()[0].getReason(), ValidationReason::INVALID_KEY);
  EXPECT_EQ(result.getEntries()[0].getPath(), "extra");
}

TEST(ObjectValidatorTest, validValueValidator) {
  auto             value = crow::json::load(R"json(
    {
      "foo": "12"
    }
  )json");
  ObjectValidator* validator =
      Object()->field("foo", String(new PatternValidator("[0-9]{2}")));
  auto result = validator->Validator::validate(value);

  EXPECT_EQ(result.isValid(), true);
}

TEST(ObjectValidatorTest, notValidValueValidator) {
  auto             value = crow::json::load(R"json(
    {
      "foo": "ab"
    }
  )json");
  ObjectValidator* validator =
      Object()->field("foo", String(new PatternValidator("[0-9]{2}")));
  auto result = validator->Validator::validate(value);

  EXPECT_EQ(result.isValid(), false);
  EXPECT_EQ(result.getEntries().size(), 1);
  EXPECT_EQ(result.getEntries()[0].getValueType(), STRING);
  EXPECT_EQ(result.getEntries()[0].getReason(),
            ValidationReason::INVALID_FORMAT);
  EXPECT_EQ(result.getEntries()[0].getPath(), "foo");
}

TEST(ObjectValidatorTest, validNested) {
  auto             value = crow::json::load(R"json(
    {
      "foo": "some string",
      "bar": {
        "nested": "woot"
      }
    }
  )json");
  ObjectValidator* validator =
      Object()
          ->field("foo", String())
          ->field("bar", Object()
                             ->field("nested", String(NOT_NULLABLE))
                             ->field("extra", String(OPTIONAL)));
  auto result = validator->Validator::validate(value);

  EXPECT_EQ(result.isValid(), true);
}

TEST(ObjectValidatorTest, invalidNested) {
  auto       value = crow::json::load(R"json(
    {
      "foo": "12",
      "bar": {
        "nested": null
      }
    }
  )json");
  Validator* validator =
      Object()
          ->field("foo", String())
          ->field("bar", Object()
                             ->field("nested", String(NOT_NULLABLE))
                             ->field("extra", String(OPTIONAL)));
  auto result = validator->validate(value);

  EXPECT_EQ(result.isValid(), false);
  EXPECT_EQ(result.getEntries().size(), 1);
  EXPECT_EQ(result.getEntries()[0].getValueType(), STRING);
  EXPECT_EQ(result.getEntries()[0].getReason(), ValidationReason::NOT_NULLABLE);
  EXPECT_EQ(result.getEntries()[0].getPath(), "bar.nested");
}
