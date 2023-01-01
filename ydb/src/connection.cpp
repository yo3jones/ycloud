#include "../include/connection.h"

namespace ydb {

Connection::Connection() {}

Connection::Connection(const DriverFactory&  driverFactory,
                       const ConnectionInfo& connectionInfo) {
  driver = shared_ptr<Driver>(driverFactory.create());
  driver->connect(connectionInfo);
}

void Connection::disconnect() {
  driver->disconnect();
}

Result Connection::exec(const std::string& query) {
  return Result(driver->exec(query));
}

}  // namespace ydb
