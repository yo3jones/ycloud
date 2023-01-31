#include "./yutil.h"
#include "gtest/gtest.h"

using yutil::schema::Array;
using yutil::schema::ARRAY;
using yutil::schema::Bool;
using yutil::schema::BOOL;
using yutil::schema::Date;
using yutil::schema::DATE;
using yutil::schema::DateTime;
using yutil::schema::DATETIME;
using yutil::schema::Float;
using yutil::schema::FLOAT;
using yutil::schema::Id;
using yutil::schema::ID;
using yutil::schema::Int;
using yutil::schema::INT;
using yutil::schema::LENIENT;
using yutil::schema::NOT_NULLABLE;
using yutil::schema::NULLABLE;
using yutil::schema::OPTIONAL;
using yutil::schema::REQIRED;
using yutil::schema::STRICT;
using yutil::schema::STRING;
using yutil::schema::String;

TEST(SchemaTest, defaultConstraint) {
  auto schema = String();

  EXPECT_EQ(schema->isOptional(), true);
  EXPECT_EQ(schema->isRequired(), false);
  EXPECT_EQ(schema->isStrict(), false);
  EXPECT_EQ(schema->isLenient(), true);
  EXPECT_EQ(schema->isNullable(), true);
  EXPECT_EQ(schema->isNotNullable(), false);

  delete schema;
}

TEST(SchemaTest, isOptional) {
  auto schema = String(OPTIONAL);

  EXPECT_EQ(schema->isOptional(), true);
  EXPECT_EQ(schema->isRequired(), false);
  EXPECT_EQ(schema->isStrict(), false);
  EXPECT_EQ(schema->isLenient(), true);
  EXPECT_EQ(schema->isNullable(), true);
  EXPECT_EQ(schema->isNotNullable(), false);

  delete schema;
}

TEST(SchemaTest, isRequired) {
  auto schema = String(REQIRED);

  EXPECT_EQ(schema->isOptional(), false);
  EXPECT_EQ(schema->isRequired(), true);
  EXPECT_EQ(schema->isStrict(), false);
  EXPECT_EQ(schema->isLenient(), true);
  EXPECT_EQ(schema->isNullable(), true);
  EXPECT_EQ(schema->isNotNullable(), false);

  delete schema;
}

TEST(SchemaTest, isStrict) {
  auto schema = String(STRICT);

  EXPECT_EQ(schema->isOptional(), true);
  EXPECT_EQ(schema->isRequired(), false);
  EXPECT_EQ(schema->isStrict(), true);
  EXPECT_EQ(schema->isLenient(), false);
  EXPECT_EQ(schema->isNullable(), true);
  EXPECT_EQ(schema->isNotNullable(), false);

  delete schema;
}

TEST(SchemaTest, isLenient) {
  auto schema = String(LENIENT);

  EXPECT_EQ(schema->isOptional(), true);
  EXPECT_EQ(schema->isRequired(), false);
  EXPECT_EQ(schema->isStrict(), false);
  EXPECT_EQ(schema->isLenient(), true);
  EXPECT_EQ(schema->isNullable(), true);
  EXPECT_EQ(schema->isNotNullable(), false);

  delete schema;
}

TEST(SchemaTest, isNullable) {
  auto schema = String(NULLABLE);

  EXPECT_EQ(schema->isOptional(), true);
  EXPECT_EQ(schema->isRequired(), false);
  EXPECT_EQ(schema->isStrict(), false);
  EXPECT_EQ(schema->isLenient(), true);
  EXPECT_EQ(schema->isNullable(), true);
  EXPECT_EQ(schema->isNotNullable(), false);

  delete schema;
}

TEST(SchemaTest, isNotNullable) {
  auto schema = String(NOT_NULLABLE);

  EXPECT_EQ(schema->isOptional(), true);
  EXPECT_EQ(schema->isRequired(), false);
  EXPECT_EQ(schema->isStrict(), false);
  EXPECT_EQ(schema->isLenient(), true);
  EXPECT_EQ(schema->isNullable(), false);
  EXPECT_EQ(schema->isNotNullable(), true);

  delete schema;
}

TEST(SchemaTest, combinedConstraint) {
  auto schema = String(REQIRED | STRICT | NOT_NULLABLE);

  EXPECT_EQ(schema->isOptional(), false);
  EXPECT_EQ(schema->isRequired(), true);
  EXPECT_EQ(schema->isStrict(), true);
  EXPECT_EQ(schema->isLenient(), false);
  EXPECT_EQ(schema->isNullable(), false);
  EXPECT_EQ(schema->isNotNullable(), true);

  delete schema;
}

TEST(SchemaTest, string) {
  auto schema = String(REQIRED | STRICT | NOT_NULLABLE);

  EXPECT_EQ(schema->getType(), STRING);
  EXPECT_EQ(schema->isOptional(), false);
  EXPECT_EQ(schema->isRequired(), true);
  EXPECT_EQ(schema->isStrict(), true);
  EXPECT_EQ(schema->isLenient(), false);
  EXPECT_EQ(schema->isNullable(), false);
  EXPECT_EQ(schema->isNotNullable(), true);

  delete schema;
}

TEST(SchemaTest, int) {
  auto schema = Int(REQIRED | STRICT | NOT_NULLABLE);

  EXPECT_EQ(schema->getType(), INT);
  EXPECT_EQ(schema->isOptional(), false);
  EXPECT_EQ(schema->isRequired(), true);
  EXPECT_EQ(schema->isStrict(), true);
  EXPECT_EQ(schema->isLenient(), false);
  EXPECT_EQ(schema->isNullable(), false);
  EXPECT_EQ(schema->isNotNullable(), true);

  delete schema;
}

TEST(SchemaTest, float) {
  auto schema = Float(REQIRED | STRICT | NOT_NULLABLE);

  EXPECT_EQ(schema->getType(), FLOAT);
  EXPECT_EQ(schema->isOptional(), false);
  EXPECT_EQ(schema->isRequired(), true);
  EXPECT_EQ(schema->isStrict(), true);
  EXPECT_EQ(schema->isLenient(), false);
  EXPECT_EQ(schema->isNullable(), false);
  EXPECT_EQ(schema->isNotNullable(), true);

  delete schema;
}

TEST(SchemaTest, bool) {
  auto schema = Bool(REQIRED | STRICT | NOT_NULLABLE);

  EXPECT_EQ(schema->getType(), BOOL);
  EXPECT_EQ(schema->isOptional(), false);
  EXPECT_EQ(schema->isRequired(), true);
  EXPECT_EQ(schema->isStrict(), true);
  EXPECT_EQ(schema->isLenient(), false);
  EXPECT_EQ(schema->isNullable(), false);
  EXPECT_EQ(schema->isNotNullable(), true);

  delete schema;
}

TEST(SchemaTest, Id) {
  auto schema = Id(REQIRED | STRICT | NOT_NULLABLE);

  EXPECT_EQ(schema->getType(), ID);
  EXPECT_EQ(schema->isOptional(), false);
  EXPECT_EQ(schema->isRequired(), true);
  EXPECT_EQ(schema->isStrict(), true);
  EXPECT_EQ(schema->isLenient(), false);
  EXPECT_EQ(schema->isNullable(), false);
  EXPECT_EQ(schema->isNotNullable(), true);

  delete schema;
}

TEST(SchemaTest, Date) {
  auto schema = Date(REQIRED | STRICT | NOT_NULLABLE);

  EXPECT_EQ(schema->getType(), DATE);
  EXPECT_EQ(schema->isOptional(), false);
  EXPECT_EQ(schema->isRequired(), true);
  EXPECT_EQ(schema->isStrict(), true);
  EXPECT_EQ(schema->isLenient(), false);
  EXPECT_EQ(schema->isNullable(), false);
  EXPECT_EQ(schema->isNotNullable(), true);

  delete schema;
}

TEST(SchemaTest, DateTime) {
  auto schema = DateTime(REQIRED | STRICT | NOT_NULLABLE);

  EXPECT_EQ(schema->getType(), DATETIME);
  EXPECT_EQ(schema->isOptional(), false);
  EXPECT_EQ(schema->isRequired(), true);
  EXPECT_EQ(schema->isStrict(), true);
  EXPECT_EQ(schema->isLenient(), false);
  EXPECT_EQ(schema->isNullable(), false);
  EXPECT_EQ(schema->isNotNullable(), true);

  delete schema;
}

TEST(SchemaTest, Array) {
  auto schema = Array(REQIRED | STRICT | NOT_NULLABLE, String());

  EXPECT_EQ(schema->getType(), ARRAY);
  EXPECT_EQ(schema->isOptional(), false);
  EXPECT_EQ(schema->isRequired(), true);
  EXPECT_EQ(schema->isStrict(), true);
  EXPECT_EQ(schema->isLenient(), false);
  EXPECT_EQ(schema->isNullable(), false);
  EXPECT_EQ(schema->isNotNullable(), true);
  EXPECT_EQ(schema->getElementsSchema().getType(), STRING);

  delete schema;
}
