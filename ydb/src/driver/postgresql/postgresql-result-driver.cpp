#include <iterator>

#include "../../../include/driver/postgresql/postgresql-result-driver.h"
#include "../../../include/driver/postgresql/postgresql-row-driver.h"
#include "../../../include/driver/row-driver.h"

using driver_ydb::RowDriver;
using postgresql_ydb::PostgresqlResultDriver;
using postgresql_ydb::PostgresqlRowDriver;

PostgresqlResultDriver::PostgresqlResultDriver(pqxx::result backingResult)
    : backingResult{backingResult} {}

int PostgresqlResultDriver::getRowCount() {
  return std::size(backingResult);
}

RowDriver* PostgresqlResultDriver::at(int i) {
  return new PostgresqlRowDriver(backingResult.at(i));
}
