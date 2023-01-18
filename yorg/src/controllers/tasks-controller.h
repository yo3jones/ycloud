#ifndef YORG_SRC_CONTROLLERS_TASKS_CONTROLLER_H_
#define YORG_SRC_CONTROLLERS_TASKS_CONTROLLER_H_
#include <string>
#include "../middleware.h"
#include "./crow.h"
#include "./ydbrestcapability.h"

namespace yorg {
namespace controllers {

using ymicroservice::DBAccessor;

class TasksController {
 public:
  explicit TasksController(DBAccessor<MIDDLEWARE>& dbAccessor);  // NOLINT

  crow::json::wvalue post(const crow::request& req);

  crow::json::wvalue get(const crow::request& req);

 private:
  DBAccessor<MIDDLEWARE>& dbAccessor;
};

}  // namespace controllers
}  // namespace yorg

#endif  // !YORG_SRC_CONTROLLERS_TASKS_CONTROLLER_H_
