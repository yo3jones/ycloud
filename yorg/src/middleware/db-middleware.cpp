#include "./db-middleware.h"

namespace yorg {

DbMiddleware::DbMiddleware() {}

void DbMiddleware::before_handle(crow::request&  req,
                                 crow::response& res,
                                 context&        ctx) {
  ctx.conn = connPool->get();
}

void DbMiddleware::after_handle(crow::request&  req,
                                crow::response& res,
                                context&        ctx) {
  connPool->release(ctx.conn);
}

void DbMiddleware::setConnectionPool(ydb::ConnectionPool& connPool) {
  this->connPool = &connPool;
}

}  // namespace yorg
