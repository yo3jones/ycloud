#include "./yutil.h"
#include "crow/json.h"
#include "gtest/gtest.h"
#include "include/rest-client.h"

TEST(foo, bar) {
  ymicroservice::RESTClient client{yutil::Env()};
  crow::json::rvalue        res = client.get("/hello");

  EXPECT_EQ(res["hello"].s(), "world");
}
