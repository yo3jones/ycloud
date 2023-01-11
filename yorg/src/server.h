#ifndef YORG_SRC_SERVER_H_
#define YORG_SRC_SERVER_H_
#include "./dependencies.h"
#include "crow.h"
#include "crow/app.h"
#include "middleware/db-middleware.h"
#include "yutil.h"

namespace yorg {

using yorg::Dependencies;
using yutil::Env;

class Server {
 public:
  Server(Env::EnvType envType);

  crow::App<DbMiddleware>& start();

 private:
  Env                           env;
  Env::EnvType                  envType;
  ConnectionInfo                connInfo;
  crow::App<yorg::DbMiddleware> app;
  Dependencies                  deps;
};

}  // namespace yorg

#endif  // !YORG_SRC_SERVER_H_
