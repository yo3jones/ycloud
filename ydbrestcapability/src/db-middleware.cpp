#include "../include/db-middleware.h"

namespace ymicroservice {

void DBMiddleware::before_handle(crow::request&  req,
                                 crow::response& res,
                                 context&        ctx) {
  ctx.conn = connPool->get();
}

void DBMiddleware::after_handle(crow::request&  req,
                                crow::response& res,
                                context&        ctx) {
  connPool->release(ctx.conn);
}

void DBMiddleware::setConnectionPool(ydb::ConnectionPool* connPool) {
  this->connPool = connPool;
}

}  // namespace ymicroservice
