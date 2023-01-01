#include <string>

#include "../../../include/driver/postgresql/postgresql-reference-driver.h"

using postgresql_ydb::PostgresqlReferenceDriver;
using std::string;

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
