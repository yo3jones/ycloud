#ifndef YDBRESTCAPABILITY_INCLUDE_DB_MIDDLEWARE_H_
#define YDBRESTCAPABILITY_INCLUDE_DB_MIDDLEWARE_H_
#include "./crow.h"
#include "./ydb.h"
#include "pqxx/pqxx"

namespace ymicroservice {

class DBMiddleware {
 public:
  struct context {
    pqxx::connection* conn;
  };

  void before_handle(crow::request&  req,  // NOLINT
                     crow::response& res,  // NOLINT
                     context&        ctx);        // NOLINT

  void after_handle(crow::request&  req,  // NOLINT
                    crow::response& res,  // NOLINT
                    context&        ctx);        // NOLINT

  void setConnectionPool(ydb::ConnectionPool* connPool);

 private:
  ydb::ConnectionPool* connPool;
};

}  // namespace ymicroservice

#endif  // !YDBRESTCAPABILITY_INCLUDE_DB_MIDDLEWARE_H_
