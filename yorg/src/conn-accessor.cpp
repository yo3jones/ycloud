#include "conn-accessor.h"

namespace yorg {

ConnAccessor::ConnAccessor(crow::App<DbMiddleware>& app,
                           ConnectionPool&          connPool)
    : app{app}, connPool{connPool} {}

pqxx::connection* ConnAccessor::get(const crow::request& req) {
  return app.get_context<DbMiddleware>(req).conn;
}

}  // namespace yorg
