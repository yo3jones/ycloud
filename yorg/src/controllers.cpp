#include "controllers.h"
#include <string>
#include "controllers/hello-controller.h"
#include "middleware/db-middleware.h"

namespace yorg {
namespace controllers {

Controllers::Controllers(crow::App<DbMiddleware>& app,
                         ConnectionPool&          connPool,
                         ConnAccessor&            connAccessor)
    : app(app),
      connPool(connPool),

      helloController(connAccessor),
      tasksController(connAccessor) {}

void Controllers::registerControllers() {
  // initialize middleware
  app.get_middleware<yorg::DbMiddleware>().setConnectionPool(connPool);

  // initilize routes
  CROW_ROUTE(app, "/hello")
      .methods(crow::HTTPMethod::GET)([this](const crow::request& req) {
        return helloController.get(req);
      });

  CROW_ROUTE(app, "/users/<string>/tasks")
      .methods(crow::HTTPMethod::POST)(
          [this](const crow::request& req, string userId) {
            return tasksController.post(req);
          });

  CROW_ROUTE(app, "/users/<string>/tasks")
      .methods(crow::HTTPMethod::GET)(
          [this](const crow::request& req, string userId) {
            return tasksController.get(req);
          });
}

}  // namespace controllers
}  // namespace yorg
