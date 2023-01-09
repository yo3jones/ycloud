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

void execInTxn(pqxx::connection&                    conn,  // NOLINT
               std::function<void(pqxx::work& txn)> fn) {  // NOLINT
  pqxx::work txn{conn};

  fn(txn);

  txn.commit();
}

void execInTxn(const ConnectionInfo&                connInfo,
               std::function<void(pqxx::work& txn)> fn) {  // NOLINT
  pqxx::connection conn{connInfo.toURI()};
  execInTxn(conn, fn);
  conn.close();
}

}  // namespace ydb
