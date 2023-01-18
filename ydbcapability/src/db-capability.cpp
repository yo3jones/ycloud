#include "../include/db-capability.h"

namespace ymicroservice {

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
