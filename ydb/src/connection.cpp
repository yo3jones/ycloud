#include <memory>
#include <string>

#include "../include/connection.h"
#include "../include/driver/driver.h"
#include "../include/result.h"

using driver_ydb::Driver;
using std::shared_ptr;
using ydb::Connection;
using ydb::Result;

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
