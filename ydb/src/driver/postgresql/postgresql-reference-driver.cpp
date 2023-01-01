#include "../../../include/driver/postgresql/postgresql-reference-driver.h"

namespace ydb {
namespace driver {
namespace postgresql {

PostgresqlReferenceDriver::PostgresqlReferenceDriver(
    pqxx::row::reference backingReference)
    : backingReference(backingReference) {}

bool PostgresqlReferenceDriver::isNull() {
  return backingReference.is_null();
}

string PostgresqlReferenceDriver::asString() {
  return backingReference.c_str();
}

int PostgresqlReferenceDriver::asInt() {
  return backingReference.as<int>();
}

}  // namespace postgresql
}  // namespace driver
}  // namespace ydb
