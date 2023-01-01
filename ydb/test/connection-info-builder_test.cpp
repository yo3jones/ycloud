#include "../include/connection-info-builder.h"
#include "gtest/gtest.h"

using ydb::ConnectionInfoBuilder;
using ydb::Type;

class ConnectionInfoBuilderTest : public ::testing::Test {
 protected:
  ConnectionInfoBuilder builder = ConnectionInfoBuilder{}
                                      .type(Type::postgresql)
                                      .host("someHost")
                                      .port("1234")
                                      .user("someUser")
                                      .password("somePassword")
                                      .database("someDatabase");
};

TEST_F(ConnectionInfoBuilderTest, type) {
  EXPECT_EQ(builder.build().getType(), Type::postgresql);
}

TEST_F(ConnectionInfoBuilderTest, host) {
  EXPECT_EQ(builder.build().getHost(), "someHost");
}

TEST_F(ConnectionInfoBuilderTest, port) {
  EXPECT_EQ(builder.build().getPort(), "1234");
}

TEST_F(ConnectionInfoBuilderTest, user) {
  EXPECT_EQ(builder.build().getUser(), "someUser");
}

TEST_F(ConnectionInfoBuilderTest, password) {
  EXPECT_EQ(builder.build().getPassword(), "somePassword");
}

TEST_F(ConnectionInfoBuilderTest, database) {
  EXPECT_EQ(builder.build().getDatabase(), "someDatabase");
}
