#include "../include/db-capability.h"

namespace ymicroservice {

using ydb::ConnectionInfo;

DBCapability::DBCapability(const Env& env)
    : _connPool(ConnectionInfo(env), env.dbPoolSize()),
      migrationsRunner(
          ConnectionInfo(env),
          ConnectionInfo(env, ConnectionInfo::USE_DEFAULT_DATABASE)) {}

ConnectionPool& DBCapability::connPool() {
  return _connPool;
}

DBCapability* DBCapability::registerMigration(Migration* migration) {
  migrationsRunner.registerMigration(migration);
  return this;
}

DBCapability* DBCapability::registerMigrations(
    const std::vector<Migration*>& migrations) {
  migrationsRunner.registerMigrations(migrations);
  return this;
}

void DBCapability::beforeStart(Capabilities& capabilities) {
  migrationsRunner.run();
}

}  // namespace ymicroservice
