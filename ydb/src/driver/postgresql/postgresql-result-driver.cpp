#include <iterator>

#include "../../../include/driver/postgresql/postgresql-result-driver.h"
#include "../../../include/driver/postgresql/postgresql-row-driver.h"

namespace ydb {
namespace driver {
namespace postgresql {

PostgresqlResultDriver::PostgresqlResultDriver(pqxx::result backingResult)
    : backingResult{backingResult} {}

int PostgresqlResultDriver::getRowCount() {
  return std::size(backingResult);
}

RowDriver* PostgresqlResultDriver::at(int i) {
  return new PostgresqlRowDriver(backingResult.at(i));
}

}  // namespace postgresql
}  // namespace driver
}  // namespace ydb
