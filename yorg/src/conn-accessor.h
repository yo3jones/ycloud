#ifndef YORG_SRC_CONN_ACCESSOR_H_
#define YORG_SRC_CONN_ACCESSOR_H_
#include "./middleware/db-middleware.h"
#include "crow.h"
#include "crow/app.h"
#include "ydb.h"

namespace yorg {

using ydb::ConnectionPool;

class ConnAccessor {
 public:
  ConnAccessor(crow::App<DbMiddleware>& app, ConnectionPool& connPool);

  pqxx::connection* get(const crow::request& req);

 private:
  crow::App<DbMiddleware>& app;
  ConnectionPool&          connPool;
};

}  // namespace yorg

#endif  // !YORG_SRC_CONN_ACCESSOR_H_
