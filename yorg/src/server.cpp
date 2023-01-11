#include "./server.h"
#include "./migrations.h"
#include "controllers.h"
#include "crow.h"
#include "ydb.h"

namespace yorg {

using ydb::ConnectionInfo;
using yutil::Env;

Server::Server(Env::EnvType envType)
    : env(),
      envType(envType),
      connInfo(
          env,
          envType == Env::TEST ? ConnectionInfo::TEST : ConnectionInfo::MAIN),
      app(),
      deps(env, connInfo, app) {}

crow::App<DbMiddleware>& Server::start() {
  ConnectionInfo defaultConnInfo{env, ConnectionInfo::DEFAULT};

  // run migrations
  deps.getMigrations().run(connInfo, defaultConnInfo);

  // initialize routes
  deps.getControllers().registerControllers();

  app.validate();

  if (envType != Env::TEST) {
    app.port(env.httpPort()).multithreaded().run();
  }

  return app;
}

}  // namespace yorg
