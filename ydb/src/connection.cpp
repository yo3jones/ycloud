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

Transaction Connection::createTransaction() {
  return Transaction(driver->createTransaction());
}

Result Connection::exec(Transaction transaction, const std::string& query) {
  return Result(driver->exec(transaction.transactionDriver.get(), query));
}

Result Connection::execNoTransaction(const std::string& query) {
  return Result(driver->execNoTransaction(query));
}

}  // namespace ydb
