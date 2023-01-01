#ifndef YDB_INCLUDE_DRIVER_POSTGRESQL_POSTGRESQL_DRIVER_FACTORY_H_
#define YDB_INCLUDE_DRIVER_POSTGRESQL_POSTGRESQL_DRIVER_FACTORY_H_
#include "../driver-factory.h"

using driver_ydb::DriverFactory;

namespace ydb {

class PostgresqlDriverFactory : public DriverFactory {
 public:
  Driver* create() const;
};

}  // namespace ydb

#endif  // !YDB_INCLUDE_DRIVER_POSTGRESQL_POSTGRESQL_DRIVER_FACTORY_H_
