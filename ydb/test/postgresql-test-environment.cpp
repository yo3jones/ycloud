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

ConnectionInfo PostgresqlTestEnvironment::defaultConnInfo =
    ConnectionInfoBuilder().build();
ConnectionInfo PostgresqlTestEnvironment::connInfo =
    ConnectionInfoBuilder().build();

PostgresqlTestEnvironment::PostgresqlTestEnvironment() {}

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
}

void PostgresqlTestEnvironment::TearDown() {
  cleanupTestDatabase(defaultConnInfo, connInfo.getDatabase());
}

Connection* PostgresqlTestEnvironment::createConnection(
    ConnectionInfo connInfo) {
  return new Connection(PostgresqlDriverFactory(), connInfo);
}

Connection* PostgresqlTestEnvironment::createConnection() {
  return createConnection(connInfo);
}

void PostgresqlTestEnvironment::cleanupTestDatabase(Connection*   conn,
                                                    const string& database) {
  conn->execNoTransaction("DROP DATABASE IF EXISTS " + database);
}

void PostgresqlTestEnvironment::cleanupTestDatabase(ConnectionInfo connInfo,
                                                    const string&  database) {
  auto connection = createConnection(connInfo);
  cleanupTestDatabase(connection, database);
  connection->disconnect();
  delete connection;
}

void PostgresqlTestEnvironment::initTestDatabase(ConnectionInfo connInfo,
                                                 const string&  database) {
  auto connection = createConnection(connInfo);
  cleanupTestDatabase(connection, database);
  connection->execNoTransaction("CREATE DATABASE " + database);
  connection->disconnect();
  delete connection;
}
