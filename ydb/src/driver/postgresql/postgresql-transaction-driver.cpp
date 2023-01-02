#include "../../../include/driver/postgresql/postgresql-transaction-driver.h"
#include "pqxx/connection.hxx"

namespace ydb {
namespace driver {
namespace postgresql {

PostgresqlTransactionDriver::PostgresqlTransactionDriver(
    pqxx::connection* backingConn)
    : backingTransaction(*backingConn) {}

void PostgresqlTransactionDriver::commit() {
  backingTransaction.commit();
}

void PostgresqlTransactionDriver::abort() {
  backingTransaction.abort();
}

}  // namespace postgresql
}  // namespace driver
}  // namespace ydb
