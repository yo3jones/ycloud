#include "./rest-client.h"
#include "./ydb.h"
#include "./yutil.h"
#include "gmock/gmock.h"
#include "pqxx/pqxx"

class TasksControllerTest : public testing::Test {
 public:
  void SetUp() override {
    cleanup();
    conn = new pqxx::connection(ydb::ConnectionInfo(yutil::Env()).toURI());
  }

  void TearDown() override {
    cleanup();
    conn->close();
    delete conn;
  }

  void cleanup() {
    yutil::Env          env;
    ydb::ConnectionInfo connInfo{env};
    pqxx::connection    conn{connInfo.toURI()};
    pqxx::work          txn{conn};

    txn.exec("TRUNCATE TABLE task");

    txn.commit();
    conn.close();
  }

  pqxx::connection* conn;
};

TEST_F(TasksControllerTest, POST) {
  yutil::Env                env;
  ymicroservice::RESTClient client{env};

  auto postRes = client.post("/users/foo/tasks", {{"name", "foo"}});

  EXPECT_EQ(postRes["data"][0]["name"].s(), "foo");
  EXPECT_THAT(
      postRes["data"][0]["id"].s(),
      testing::MatchesRegex("^[0-f]{8}-[0-f]{4}-[0-f]{4}-[0-f]{4}-[0-f]{12}$"));
  EXPECT_THAT(
      string(postRes["data"][0]["createdAt"].s()),
      testing::MatchesRegex("^[0-9]{4}-[0-9]{2}-[0-9]{2}"
                            "T[0-9]{2}:[0-9]{2}:[0-9]{2}\\.[0-9]{3}Z$"));
  EXPECT_THAT(
      string(postRes["data"][0]["updatedAt"].s()),
      testing::MatchesRegex("^[0-9]{4}-[0-9]{2}-[0-9]{2}"
                            "T[0-9]{2}:[0-9]{2}:[0-9]{2}\\.[0-9]{3}Z$"));

  string               id = postRes["data"][0]["id"].s();
  pqxx::nontransaction txn{*conn};
  auto                 sqlRes = txn.exec_params("SELECT * FROM task");

  EXPECT_EQ(sqlRes.size(), 1);
  EXPECT_EQ(string(sqlRes[0]["name"].c_str()), "foo");
  EXPECT_EQ(string(sqlRes[0]["id"].c_str()), id);
}

TEST_F(TasksControllerTest, GET) {
  yutil::Env                env;
  ymicroservice::RESTClient client{env};

  auto res1 = client.post("/users/foo/tasks", {{"name", "foo"}});
  auto res2 = client.post("/users/foo/tasks", {{"name", "bar"}});

  auto got = client.get("/users/foo/tasks");

  EXPECT_EQ(got["data"][0]["name"].s(), "foo");
  EXPECT_EQ(got["data"][0]["id"].s(), res1["data"][0]["id"].s());
  EXPECT_EQ(got["data"][1]["name"].s(), "bar");
  EXPECT_EQ(got["data"][1]["id"].s(), res2["data"][0]["id"].s());
}
