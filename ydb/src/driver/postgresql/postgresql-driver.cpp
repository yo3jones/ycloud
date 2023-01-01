#include <iostream>
#include <memory>
#include <string>

#include "../../../include/driver/postgresql/postgresql-driver.h"
#include "../../../include/driver/postgresql/postgresql-result-driver.h"
#include "../../../include/driver/result-driver.h"
#include "pqxx/pqxx"

using driver_ydb::ResultDriver;
using postgresql_ydb::PostgresqlDriver;
using postgresql_ydb::PostgresqlResultDriver;
using std::shared_ptr;
using ydb::ConnectionInfo;

string PostgresqlDriver::buildConnectionString(
    const ConnectionInfo& connectionInfo) {
  return "postgresql://" + connectionInfo.getUser() + ":" +
         connectionInfo.getPassword() + "@" + connectionInfo.getHost() + "/" +
         connectionInfo.getDatabase();
}

PostgresqlDriver::PostgresqlDriver() : backingConnection() {}

void PostgresqlDriver::connect(const ConnectionInfo& connectionInfo) {
  backingConnection = shared_ptr<pqxx::connection>(
      new pqxx::connection(buildConnectionString(connectionInfo)));
}

void PostgresqlDriver::disconnect() {
  backingConnection->disconnect();
}

ResultDriver* PostgresqlDriver::exec(const string& query) {
  pqxx::nontransaction w{*backingConnection};

  pqxx::result backingResult = w.exec(query);

  return new PostgresqlResultDriver(backingResult);
}
