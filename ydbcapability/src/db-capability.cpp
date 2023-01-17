#include "../include/db-capability.h"

namespace ymicroservice {

using ydb::ConnectionInfo;

DBCapability::DBCapability(const Env& env)
    : connInfo(env),
      _connPool(connInfo, env.dbPoolSize()),
      migrationsRunner(
          connInfo,
          ConnectionInfo(env, ConnectionInfo::USE_DEFAULT_DATABASE)) {}

ConnectionPool* DBCapability::connPool() {
  return &_connPool;
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

void DBCapability::beforeStart(const ROTypeMap& capabilities) {
  migrationsRunner.run();
}

}  // namespace ymicroservice
