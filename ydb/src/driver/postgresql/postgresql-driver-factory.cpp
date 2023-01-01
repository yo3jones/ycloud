#include "../../../include/driver/postgresql/postgresql-driver-factory.h"
#include "../../../include/driver/postgresql/postgresql-driver.h"

namespace ydb {

using driver::Driver;
using driver::postgresql::PostgresqlDriver;

Driver* PostgresqlDriverFactory::create() const {
  return new PostgresqlDriver();
}

}  // namespace ydb
