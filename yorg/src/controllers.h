#ifndef YORG_SRC_CONTROLLERS_H_
#define YORG_SRC_CONTROLLERS_H_
#include "conn-accessor.h"
#include "controllers/hello-controller.h"
#include "controllers/tasks-controller.h"
#include "crow.h"
#include "middleware/db-middleware.h"

namespace yorg {
namespace controllers {

class Controllers {
 public:
  Controllers(crow::App<DbMiddleware>& app, ConnAccessor& connAccessor);

  void registerControllers();

 private:
  crow::App<DbMiddleware>& app;

  HelloController helloController;
  TasksController tasksController;
};

}  // namespace controllers
}  // namespace yorg

#endif  // !YORG_SRC_CONTROLLERS_H_
