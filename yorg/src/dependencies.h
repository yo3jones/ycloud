#ifndef YORG_SRC_DEPENDENCIES_H_
#define YORG_SRC_DEPENDENCIES_H_
#include "./conn-accessor.h"
#include "./middleware/db-middleware.h"
#include "./migrations.h"
#include "controllers.h"
#include "controllers/hello-controller.h"
#include "crow.h"
#include "ydb.h"

namespace yorg {

using controllers::Controllers;
using ydb::ConnectionInfo;
using ydb::ConnectionPool;
using yorg::migrations::Migrations;
using yutil::Env;

class Dependencies {
 public:
  Dependencies(const Env&               env,
               const ConnectionInfo&    connInfo,
               crow::App<DbMiddleware>& app);

  Migrations&     getMigrations();
  ConnectionPool& getConnectionPool();
  ConnAccessor&   getConnAccessor();
  Controllers&    getControllers();

 private:
  Migrations     migrations;
  ConnectionPool connPool;
  ConnAccessor   connAccessor;
  Controllers    controllers;
};

}  // namespace yorg

#endif  // !YORG_SRC_DEPENDENCIES_H_
