#include "./dependencies.h"
#include "controllers/hello-controller.h"

namespace yorg {

Dependencies::Dependencies(const Env&               env,
                           const ConnectionInfo&    connInfo,
                           crow::App<DbMiddleware>& app)
    : migrations{},
      connPool{connInfo, env.dbPoolSize()},
      connAccessor{app, connPool},
      controllers{app, connPool, connAccessor} {}

Migrations& Dependencies::getMigrations() {
  return migrations;
}

ConnectionPool& Dependencies::getConnectionPool() {
  return connPool;
}

ConnAccessor& Dependencies::getConnAccessor() {
  return connAccessor;
}

Controllers& Dependencies::getControllers() {
  return controllers;
}

}  // namespace yorg
