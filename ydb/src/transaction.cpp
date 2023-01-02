#include "../include/transaction.h"

namespace ydb {

Transaction::Transaction(TransactionDriver* transactionDriver)
    : transactionDriver(transactionDriver) {}

void Transaction::commit() {
  transactionDriver->commit();
}

void Transaction::abort() {
  transactionDriver->abort();
}

}  // namespace ydb
