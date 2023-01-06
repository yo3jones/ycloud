#include "./ydb.h"
#include "pqxx/pqxx"

namespace ydb {

void createDatabase(ConnectionInfo defaultConnInfo,
                    const string&  databaseName) {
  pqxx::connection     conn{defaultConnInfo.toURI()};
  pqxx::nontransaction txn{conn};

  try {
    txn.exec("CREATE DATABASE " + databaseName);
  } catch (...) {
    // database already exists
  }

  conn.close();
}

}  // namespace ydb
