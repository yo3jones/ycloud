#include "./migration.h"

namespace ydb {

void Migration::up(pqxx::connection& conn) {
  pqxx::work txn{conn};

  this->up(txn);

  txn.commit();
}

void Migration::up(pqxx::work& txn) {}

}  // namespace ydb
