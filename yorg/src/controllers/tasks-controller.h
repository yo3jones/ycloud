#ifndef YORG_SRC_CONTROLLERS_TASKS_CONTROLLER_H_
#define YORG_SRC_CONTROLLERS_TASKS_CONTROLLER_H_
#include <string>
#include "../conn-accessor.h"
#include "crow.h"

namespace yorg {
namespace controllers {

class TasksController {
 public:
  TasksController(ConnAccessor& connAccessor);

  crow::json::wvalue post(const crow::request& req);

  crow::json::wvalue get(const crow::request& req);

 private:
  ConnAccessor& connAccessor;
};

}  // namespace controllers
}  // namespace yorg

#endif  // !YORG_SRC_CONTROLLERS_TASKS_CONTROLLER_H_
