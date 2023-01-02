#include "../include/connection-info.h"
#include "gtest/gtest.h"

using ydb::ConnectionInfo;
using ydb::Type;

class ConnectionInfoTest : public ::testing::Test {
 protected:
  ConnectionInfo connInfo{Type::postgresql, "someHost",     "1234",
                          "someUser",       "somePassword", "someDatabase"};
};

TEST_F(ConnectionInfoTest, getType) {
  EXPECT_EQ(connInfo.getType(), Type::postgresql);
}

TEST_F(ConnectionInfoTest, getHost) {
  EXPECT_EQ(connInfo.getHost(), "someHost");
}

TEST_F(ConnectionInfoTest, getPort) {
  EXPECT_EQ(connInfo.getPort(), "1234");
}

TEST_F(ConnectionInfoTest, getUser) {
  EXPECT_EQ(connInfo.getUser(), "someUser");
}

TEST_F(ConnectionInfoTest, getPassword) {
  EXPECT_EQ(connInfo.getPassword(), "somePassword");
}

TEST_F(ConnectionInfoTest, getDatabase) {
  EXPECT_EQ(connInfo.getDatabase(), "someDatabase");
}

TEST_F(ConnectionInfoTest, toURI) {
  EXPECT_EQ(connInfo.toURI(),
            "postgresql://someUser:somePassword@someHost:1234/someDatabase");
}
