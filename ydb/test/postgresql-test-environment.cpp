#include "../src/connection-info.h"
#include "./postgresql-test-enviornment.h"
#include "./yutil.h"

using ydb::ConnectionInfo;

namespace ydb {
namespace testing {

ConnectionInfo PostgresqlTestEnvironment::defaultConnInfo = ConnectionInfo();
ConnectionInfo PostgresqlTestEnvironment::connInfo        = ConnectionInfo();

PostgresqlTestEnvironment::PostgresqlTestEnvironment() {
  yutil::Env env;
  defaultConnInfo  = ConnectionInfo(env, ConnectionInfo::DEFAULT);
  connInfo         = ConnectionInfo(env, ConnectionInfo::TEST);
  migrationsRunner = new MigrationsRunner(connInfo, defaultConnInfo);
}

PostgresqlTestEnvironment::PostgresqlTestEnvironment(Migration* migrations[],
                                                     size_t     size) {
  yutil::Env env;
  defaultConnInfo  = ConnectionInfo(env, ConnectionInfo::DEFAULT);
  connInfo         = ConnectionInfo(env, ConnectionInfo::TEST);
  migrationsRunner = new MigrationsRunner(connInfo, defaultConnInfo);
  migrationsRunner->registerMigrations(migrations, size);
}

PostgresqlTestEnvironment::~PostgresqlTestEnvironment() {
  delete migrationsRunner;
}

void PostgresqlTestEnvironment::SetUp() {
  initTestDatabase(defaultConnInfo, connInfo.getDatabase());

  migrationsRunner->run();
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

  conn->close();
  delete conn;
}

}  // namespace testing
}  // namespace ydb
