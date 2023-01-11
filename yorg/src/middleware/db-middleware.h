#ifndef YORG_SRC_MIDDLEWARE_DB_MIDDLEWARE_H_
#define YORG_SRC_MIDDLEWARE_DB_MIDDLEWARE_H_
#include <string>
#include "crow.h"
#include "ydb.h"

namespace yorg {

class DbMiddleware {
 public:
  struct context {
    pqxx::connection* conn;
  };

  DbMiddleware();

  void before_handle(crow::request& req, crow::response& res, context& ctx);

  void after_handle(crow::request& req, crow::response& res, context& ctx);

  void setConnectionPool(ydb::ConnectionPool& connPool);

 private:
  ydb::ConnectionPool* connPool;
};

}  // namespace yorg

#endif  // !YORG_SRC_MIDDLEWARE_DB_MIDDLEWARE_H_
