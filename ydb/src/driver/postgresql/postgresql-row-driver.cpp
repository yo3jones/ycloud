#include "../../../include/driver/postgresql/postgresql-row-driver.h"
#include "../../../include/driver/postgresql/postgresql-reference-driver.h"
#include "../../../include/driver/reference-driver.h"
#include "pqxx/pqxx"

using driver_ydb::ReferenceDriver;
using postgresql_ydb::PostgresqlReferenceDriver;
using postgresql_ydb::PostgresqlRowDriver;

PostgresqlRowDriver::PostgresqlRowDriver(pqxx::row backingRow)
    : backingRow(backingRow) {}

ReferenceDriver* PostgresqlRowDriver::at(int i) {
  return new PostgresqlReferenceDriver(backingRow.at(i));
}

ReferenceDriver* PostgresqlRowDriver::at(const string& column) {
  return new PostgresqlReferenceDriver(backingRow.at(column));
}
