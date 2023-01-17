#ifndef YDBRESTCAPABILITY_INCLUDE_DB_ACCESSOR_H_
#define YDBRESTCAPABILITY_INCLUDE_DB_ACCESSOR_H_
#include "./crow.h"
#include "./db-middleware.h"
#include "pqxx/pqxx"

namespace ymicroservice {

template <typename... Middleware>
class DBAccessor {
 public:
  pqxx::connection* conn(const crow::request& req) {
    auto& ctx = *reinterpret_cast<crow::detail::context<Middleware...>*>(
        req.middleware_context);
    auto& dbContext = ctx.template get<DBMiddleware>();
    return dbContext.conn;
  }
};

}  // namespace ymicroservice

#endif  // !YDBRESTCAPABILITY_INCLUDE_DB_ACCESSOR_H_
