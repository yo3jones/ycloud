#include "./connection-pool.h"

namespace ydb {

ConnectionPool::ConnectionPool(const ConnectionInfo& connInfo,
                               int                   maxConnections)
    : yutil::Pool<pqxx::connection>(
          maxConnections,
          [connInfo]() -> pqxx::connection* {
            return new pqxx::connection(connInfo.toURI());
          },
          [](pqxx::connection* conn) { delete conn; }) {}

}  // namespace ydb
