#ifndef YDB_SRC_CONNECTION_POOL_H_
#define YDB_SRC_CONNECTION_POOL_H_
#include "./connection-info.h"
#include "./yutil.h"
#include "pqxx/pqxx"

namespace ydb {

class ConnectionPool : public yutil::Pool<pqxx::connection> {
 public:
  ConnectionPool(ConnectionInfo connInfo, int maxConnections);
};

}  // namespace ydb

#endif  // !YDB_SRC_CONNECTION_POOL_H_
