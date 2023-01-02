#ifndef YDB_INCLUDE_DRIVER_POSTGRESQL_POSTGRESQL_TRANSACTION_DRIVER_H_
#define YDB_INCLUDE_DRIVER_POSTGRESQL_POSTGRESQL_TRANSACTION_DRIVER_H_
#include "../transaction-driver.h"
#include "./postgresql-driver.h"
#include "pqxx/pqxx"

namespace ydb {
namespace driver {
namespace postgresql {

class PostgresqlTransactionDriver : public TransactionDriver {
 public:
  explicit PostgresqlTransactionDriver(pqxx::connection* backingConn);

  void commit();
  void abort();

 protected:
  pqxx::work backingTransaction;

  friend PostgresqlDriver;
};

}  // namespace postgresql
}  // namespace driver
}  // namespace ydb

#endif  // !YDB_INCLUDE_DRIVER_POSTGRESQL_POSTGRESQL_TRANSACTION_DRIVER_H_
