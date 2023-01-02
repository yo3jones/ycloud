#ifndef YDB_INCLUDE_TRANSACTION_H_
#define YDB_INCLUDE_TRANSACTION_H_
#include <memory>
#include "driver/transaction-driver.h"

using std::shared_ptr;

namespace ydb {

using driver::TransactionDriver;

class Transaction {
 public:
  explicit Transaction(TransactionDriver* transactionDriver);

  void commit();
  void abort();

 protected:
  shared_ptr<TransactionDriver> transactionDriver;

  friend class Connection;
};

}  // namespace ydb

#endif  // !YDB_INCLUDE_TRANSACTION_H_
