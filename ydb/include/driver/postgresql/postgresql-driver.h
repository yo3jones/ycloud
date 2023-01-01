#ifndef YDB_INCLUDE_DRIVER_POSTGRESQL_POSTGRESQL_DRIVER_H_
#define YDB_INCLUDE_DRIVER_POSTGRESQL_POSTGRESQL_DRIVER_H_
#include <memory>
#include <string>

#include "../../../include/driver/result-driver.h"
#include "../../connection-info.h"
#include "../driver.h"
#include "pqxx/pqxx"

using std::shared_ptr;

namespace ydb {
namespace driver {
namespace postgresql {

class PostgresqlDriver : public Driver {
 public:
  PostgresqlDriver();

  void connect(const ConnectionInfo& connectionInfo);
  void disconnect();

  ResultDriver* exec(const string& query);

 private:
  shared_ptr<pqxx::connection> backingConnection;

  static string buildConnectionString(const ConnectionInfo& connectionInfo);
};

}  // namespace postgresql
}  // namespace driver
}  // namespace ydb

#endif  // !YDB_INCLUDE_DRIVER_POSTGRESQL_POSTGRESQL_DRIVER_H_
