#include "../include/connection-info-builder.h"
#include "../include/connection-info.h"
#include "../include/connection.h"
#include "../include/driver/postgresql/postgresql-driver-factory.h"
#include "./include/postgresql-test-enviornment.h"
#include "gtest/gtest.h"

using std::getenv;
using ydb::Connection;
using ydb::ConnectionInfo;
using ydb::ConnectionInfoBuilder;
using ydb::PostgresqlDriverFactory;
using ydb::Type;

Connection* PostgresqlTestEnvironment::conn = nullptr;

PostgresqlTestEnvironment::PostgresqlTestEnvironment()
    : defaultConnInfo(ConnectionInfoBuilder().build()),
      connInfo(ConnectionInfoBuilder().build()) {}

PostgresqlTestEnvironment::~PostgresqlTestEnvironment() {}

void PostgresqlTestEnvironment::SetUp() {
  defaultConnInfo = ConnectionInfoBuilder()
                        .type(Type::postgresql)
                        .host(getenv("DB_HOST"))
                        .port(getenv("DB_PORT"))
                        .user(getenv("DB_USER"))
                        .password(getenv("DB_PASSWORD"))
                        .database(getenv("DB_DEFAULT_DATABASE"))
                        .build();
  connInfo = ConnectionInfoBuilder(defaultConnInfo)
                 .database(getenv("DB_TEST_DATABASE"))
                 .build();

  initTestDatabase(defaultConnInfo, connInfo.getDatabase());

  conn = new Connection{PostgresqlDriverFactory(), connInfo};
}

void PostgresqlTestEnvironment::TearDown() {
  conn->disconnect();
  cleanupTestDatabase(defaultConnInfo, connInfo.getDatabase());

  delete conn;
}

void PostgresqlTestEnvironment::cleanupTestDatabase(Connection*   conn,
                                                    const string& database) {
  conn->exec("DROP DATABASE IF EXISTS " + database);
}

void PostgresqlTestEnvironment::cleanupTestDatabase(ConnectionInfo connInfo,
                                                    const string&  database) {
  Connection connection{PostgresqlDriverFactory(), connInfo};
  cleanupTestDatabase(&connection, database);
  connection.disconnect();
}

void PostgresqlTestEnvironment::initTestDatabase(ConnectionInfo connInfo,
                                                 const string&  database) {
  Connection connection{PostgresqlDriverFactory(), connInfo};
  cleanupTestDatabase(&connection, database);
  connection.exec("CREATE DATABASE " + database);
  connection.disconnect();
}
