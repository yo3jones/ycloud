#ifndef YDB_INCLUDE_CONNECTION_H_
#define YDB_INCLUDE_CONNECTION_H_
#include <memory>
#include <string>
#include "./connection-info.h"
#include "./result.h"
#include "./transaction.h"
#include "driver/driver-factory.h"
#include "driver/driver.h"
#include "driver/transaction-driver.h"

using std::shared_ptr;
using std::string;

namespace ydb {

using driver::Driver;
using driver::DriverFactory;

class Connection {
 public:
  Connection();
  Connection(const DriverFactory&  driverFactory,
             const ConnectionInfo& connectionInfo);

  void   disconnect();
  Result exec(const string& query);

  Transaction createTransaction();
  Result      exec(Transaction transaction, const string& query);

  Result execNoTransaction(const string& query);

 private:
  shared_ptr<Driver> driver;
};

}  // namespace ydb

#endif  // YDB_INCLUDE_CONNECTION_H_
