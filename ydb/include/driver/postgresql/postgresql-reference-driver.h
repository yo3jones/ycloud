#ifndef YDB_INCLUDE_DRIVER_POSTGRESQL_POSTGRESQL_REFERENCE_DRIVER_H_
#define YDB_INCLUDE_DRIVER_POSTGRESQL_POSTGRESQL_REFERENCE_DRIVER_H_
#include <string>
#include "../reference-driver.h"
#include "pqxx/pqxx"

using driver_ydb::ReferenceDriver;
using std::string;

namespace postgresql_ydb {

class PostgresqlReferenceDriver : public ReferenceDriver {
 public:
  explicit PostgresqlReferenceDriver(pqxx::row::reference backingReference);

  bool   isNull();
  string asString();
  int    asInt();

 private:
  pqxx::row::reference backingReference;
};

}  // namespace postgresql_ydb

#endif  // !YDB_INCLUDE_DRIVER_POSTGRESQL_POSTGRESQL_REFERENCE_DRIVER_H_
