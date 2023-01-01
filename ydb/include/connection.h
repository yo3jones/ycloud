#ifndef YDB_INCLUDE_CONNECTION_H_
#define YDB_INCLUDE_CONNECTION_H_
#include <memory>
#include <string>
#include "./connection-info.h"
#include "./result.h"
#include "driver/driver-factory.h"
#include "driver/driver.h"

using driver_ydb::DriverFactory;
using std::shared_ptr;
using std::string;
using ydb::Result;

namespace ydb {

class Connection {
 public:
  Connection();
  Connection(const DriverFactory&  driverFactory,
             const ConnectionInfo& connectionInfo);

  void   disconnect();
  Result exec(const string& query);

 private:
  shared_ptr<Driver> driver;
};

}  // namespace ydb

#endif  // YDB_INCLUDE_CONNECTION_H_
