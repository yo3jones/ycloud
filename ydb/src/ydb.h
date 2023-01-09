#ifndef YDB_SRC_YDB_H_
#define YDB_SRC_YDB_H_
#include <functional>
#include <string>
#include "./connection-info.h"
#include "pqxx/pqxx"

namespace ydb {

void createDatabase(ConnectionInfo defaultConnInfo, const string& databaseName);

void execInTxn(pqxx::connection&                    conn,  // NOLINT
               std::function<void(pqxx::work& txn)> fn);   // NOLINT
                                                           //
void execInTxn(const ConnectionInfo&                connInfo,
               std::function<void(pqxx::work& txn)> fn);  // NOLINT

}  // namespace ydb

#endif  // !YDB_SRC_YDB_H_
