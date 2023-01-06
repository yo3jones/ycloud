#include "./migration.h"

namespace ydb {

Migration::~Migration() {}

void Migration::up(pqxx::connection& conn) {
  pqxx::work txn{conn};

  this->up(txn);

  txn.commit();
}

void Migration::up(pqxx::work& txn) {}

}  // namespace ydb
