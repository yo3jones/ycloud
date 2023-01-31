#include <string>
#include <unordered_set>
#include "./yutil.h"
#include "gtest/gtest.h"

using std::string;
using std::unordered_set;
using yutil::schema::DEFALT;
using yutil::schema::OBJECT;
using yutil::schema::Object;
using yutil::schema::ObjectSchema;
using yutil::schema::REQIRED;
using yutil::schema::STRING;
using yutil::schema::String;

TEST(ObjectSchemaTest, at) {
  ObjectSchema schema{{{"name", String(REQIRED)}}};

  EXPECT_EQ(schema.at("name").getType(), STRING);
  EXPECT_EQ(schema.at("name").getConstraint(), REQIRED);
  EXPECT_EQ(schema["name"].getType(), STRING);
  EXPECT_EQ(schema.contains("missing"), false);
  EXPECT_EQ(schema.contains("name"), true);
}

TEST(ObjectSchemaTest, iterator) {
  ObjectSchema schema{{{"foo", String()}, {"bar", String()}}};

  unordered_set<string> gotKeys{};
  for (auto [key, field] : schema) {
    gotKeys.emplace(key);

    EXPECT_EQ(field->getType(), STRING);
    EXPECT_EQ(field->getConstraint(), DEFALT);
  }

  EXPECT_EQ(gotKeys.size(), 2);
  EXPECT_EQ(gotKeys.contains("foo"), true);
  EXPECT_EQ(gotKeys.contains("bar"), true);
}

TEST(ObjectSchemaTest, nested) {
  ObjectSchema schema(
      {{"one", String()},
       {"two", String()},
       {"foo",
        Object({{"one", String()}, {"two", String()}, {"bar", String()}})}});

  EXPECT_EQ(schema.at("foo").getType(), OBJECT);
  EXPECT_EQ(schema.atc<ObjectSchema>("foo").at("bar").getType(), STRING);
}
