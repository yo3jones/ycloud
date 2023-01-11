#include "controllers.h"
#include <string>
#include "controllers/hello-controller.h"

namespace yorg {
namespace controllers {

Controllers::Controllers(crow::App<DbMiddleware>& app,
                         ConnAccessor&            connAccessor)
    : app(app),

      helloController(connAccessor),
      tasksController(connAccessor) {}

void Controllers::registerControllers() {
  CROW_ROUTE(app, "/hello")
      .methods(crow::HTTPMethod::GET)([this](const crow::request& req) {
        return helloController.get(req);
      });

  CROW_ROUTE(app, "/users/<string>/tasks")
      .methods(crow::HTTPMethod::POST)(
          [this](const crow::request& req, string userId) {
            return tasksController.post(req);
          });
}

}  // namespace controllers
}  // namespace yorg
