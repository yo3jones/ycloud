#include "./tasks-controller.h"
#include <ctime>
#include "crow/json.h"
#include "yutil.h"

namespace yorg {
namespace controllers {

TasksController::TasksController(ConnAccessor& connAccessor)
    : connAccessor{connAccessor} {}

crow::json::wvalue TasksController::post(const crow::request& req) {
  auto        body = crow::json::load(req.body);
  string      name = body["name"].s();
  yutil::UUID id;
  time_t      now = time(0);
  tm*         dt  = gmtime(&now);

  std::cout << dt->tm_year << std::endl;

  pqxx::connection* conn = connAccessor.get(req);
  pqxx::work        txn{*conn};

  txn.exec_params(R"sql(
      INSERT INTO task
      (id, name)
      VALUES ($1, $2)
    )sql",
                  id.toString(), name);

  txn.commit();

  return {{"id", id.toString()}, {"name", name}, {"updated_at", ""}};
}

}  // namespace controllers
}  // namespace yorg
