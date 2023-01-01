#ifndef YDB_INCLUDE_DRIVER_POSTGRESQL_POSTGRESQL_RESULT_DRIVER_H_
#define YDB_INCLUDE_DRIVER_POSTGRESQL_POSTGRESQL_RESULT_DRIVER_H_
#include "../result-driver.h"
#include "../row-driver.h"
#include "pqxx/pqxx"

using driver_ydb::ResultDriver;
using driver_ydb::RowDriver;

namespace postgresql_ydb {

class PostgresqlResultDriver : public ResultDriver {
 public:
  explicit PostgresqlResultDriver(pqxx::result backingResult);

  int        getRowCount();
  RowDriver* at(int i);

 private:
  pqxx::result backingResult;
};

}  // namespace postgresql_ydb

#endif  // !YDB_INCLUDE_DRIVER_POSTGRESQL_POSTGRESQL_RESULT_DRIVER_H_
