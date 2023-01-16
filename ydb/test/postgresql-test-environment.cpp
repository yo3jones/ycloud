#include "../src/ydb.h"
#include "./postgresql-test-enviornment.h"
#include "./yutil.h"

using ydb::ConnectionInfo;

namespace ydb {
namespace testing {

ConnectionInfo PostgresqlTestEnvironment::defaultConnInfo = ConnectionInfo();
ConnectionInfo PostgresqlTestEnvironment::connInfo        = ConnectionInfo();

PostgresqlTestEnvironment::PostgresqlTestEnvironment() {
  yutil::Env env;
  defaultConnInfo  = ConnectionInfo(env, ConnectionInfo::USE_DEFAULT_DATABASE);
  connInfo         = ConnectionInfo(env);
  migrationsRunner = new MigrationsRunner(connInfo, defaultConnInfo);
}

PostgresqlTestEnvironment::PostgresqlTestEnvironment(
    const vector<Migration*>& migrations) {
  yutil::Env env;
  defaultConnInfo  = ConnectionInfo(env, ConnectionInfo::USE_DEFAULT_DATABASE);
  connInfo         = ConnectionInfo(env);
  migrationsRunner = new MigrationsRunner(connInfo, defaultConnInfo);
  migrationsRunner->registerMigrations(migrations);
}

PostgresqlTestEnvironment::~PostgresqlTestEnvironment() {
  delete migrationsRunner;
}

void PostgresqlTestEnvironment::SetUp() {
  cleanupTestDatabase(defaultConnInfo, connInfo.getDatabase());

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

void PostgresqlTestEnvironment::execInTxn(
    std::function<void(pqxx::work& txn)> fn) {  // NOLINT
  ydb::execInTxn(connInfo, fn);
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

}  // namespace testing
}  // namespace ydb
