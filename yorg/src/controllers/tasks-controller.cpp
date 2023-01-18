#include <ctime>
#include <unordered_map>
#include <vector>

#include "./tasks-controller.h"
#include "./yutil.h"
#include "crow/json.h"

namespace yorg {
namespace controllers {

TasksController::TasksController(DBAccessor<MIDDLEWARE>& dbAccessor)
    : dbAccessor(dbAccessor) {}

crow::json::wvalue TasksController::post(const crow::request& req) {
  auto   body = crow::json::load(req.body);
  string name = body["name"].s();
  string id   = yutil::UUID().toString();
  string now  = yutil::DateTime().toISO();

  pqxx::connection* conn = dbAccessor.conn(req);
  pqxx::work        txn{*conn};

  txn.exec_params(R"sql(
      INSERT INTO task
      (id, name, updated_at, created_at)
      VALUES ($1, $2, $3, $4)
    )sql",
                  id, name, now, now);

  txn.commit();

  return {{"data", std::vector<crow::json::wvalue>{{{"id", id},
                                                    {"name", name},
                                                    {"updatedAt", now},
                                                    {"createdAt", now}}}}};

  return {{"id", id}, {"name", name}, {"updatedAt", now}, {"createdAt", now}};
}

crow::json::wvalue TasksController::get(const crow::request& req) {
  pqxx::connection* conn = dbAccessor.conn(req);
  pqxx::work        txn{*conn};

  auto                            res = txn.exec("SELECT * FROM task");
  std::vector<crow::json::wvalue> data;

  for (auto row : res) {
    data.emplace_back(std::unordered_map<string, crow::json::wvalue>{
        {"id", row["id"].c_str()},
        {"name", row["name"].c_str()},
        {"updatedAt", yutil::DateTime(row["updated_at"].c_str()).toISO()},
        {"createdAt", yutil::DateTime(row["created_at"].c_str()).toISO()}});
  }

  return {{"data", data}};
}

}  // namespace controllers
}  // namespace yorg
