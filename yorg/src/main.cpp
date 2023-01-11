#include "./dependencies.h"
#include "./migrations.h"
#include "controllers.h"
#include "controllers/hello-controller.h"
#include "crow.h"
#include "middleware/db-middleware.h"
#include "ydb.h"

using ydb::ConnectionInfo;
using yorg::Dependencies;
using yutil::Env;

int main() {
  Env                           env;
  ConnectionInfo                connInfo{env, ConnectionInfo::MAIN};
  ConnectionInfo                defaultConnInfo{env, ConnectionInfo::DEFAULT};
  crow::App<yorg::DbMiddleware> app;
  Dependencies                  deps{env, connInfo, app};

  // run migrations
  deps.getMigrations().run(connInfo, defaultConnInfo);

  // initialize middleware
  app.get_middleware<yorg::DbMiddleware>().setConnectionPool(
      deps.getConnectionPool());

  // initialize routes
  deps.getControllers().registerControllers();

  app.port(env.httpPort()).multithreaded().run();

  return 0;
}
