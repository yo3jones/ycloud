#include "../../../include/driver/postgresql/postgresql-driver-factory.h"
#include "../../../include/driver/postgresql/postgresql-driver.h"

using driver_ydb::Driver;
using postgresql_ydb::PostgresqlDriver;
using ydb::PostgresqlDriverFactory;

Driver* PostgresqlDriverFactory::create() const {
  return new PostgresqlDriver();
}
