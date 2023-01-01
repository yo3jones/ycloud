#include "../../../include/driver/postgresql/postgresql-row-driver.h"
#include "../../../include/driver/postgresql/postgresql-reference-driver.h"

namespace ydb {
namespace driver {
namespace postgresql {

PostgresqlRowDriver::PostgresqlRowDriver(pqxx::row backingRow)
    : backingRow(backingRow) {}

ReferenceDriver* PostgresqlRowDriver::at(int i) {
  return new PostgresqlReferenceDriver(backingRow.at(i));
}

ReferenceDriver* PostgresqlRowDriver::at(const string& column) {
  return new PostgresqlReferenceDriver(backingRow.at(column));
}

}  // namespace postgresql
}  // namespace driver
}  // namespace ydb
