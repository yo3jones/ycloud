#include "../src/connection-info-builder.h"
#include "./postgresql-test-enviornment.h"

using std::getenv;
using ydb::ConnectionInfo;
using ydb::ConnectionInfoBuilder;
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

pqxx::connection* PostgresqlTestEnvironment::createConnection(
    ConnectionInfo connInfo) {
  return new pqxx::connection(connInfo.toURI());
}

pqxx::connection* PostgresqlTestEnvironment::createConnection() {
  return createConnection(connInfo);
}

void PostgresqlTestEnvironment::cleanupTestDatabase(pqxx::connection* conn,
                                                    const string& database) {
  auto txn = new pqxx::nontransaction(*conn);
  txn->exec("DROP DATABASE IF EXISTS " + database);
  delete txn;
}

void PostgresqlTestEnvironment::cleanupTestDatabase(ConnectionInfo connInfo,
                                                    const string&  database) {
  auto connection = createConnection(connInfo);
  cleanupTestDatabase(connection, database);
  connection->close();
  delete connection;
}

void PostgresqlTestEnvironment::initTestDatabase(ConnectionInfo connInfo,
                                                 const string&  database) {
  auto conn = createConnection(connInfo);

  cleanupTestDatabase(conn, database);

  auto txn = new pqxx::nontransaction(*conn);
  txn->exec("CREATE DATABASE " + database);
  delete txn;

  conn->close();
  delete conn;
}
