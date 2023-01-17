#ifndef YDBCAPABILITY_INCLUDE_DB_CAPABILITY_H_
#define YDBCAPABILITY_INCLUDE_DB_CAPABILITY_H_
#include <vector>
#include "./ydb.h"
#include "./ymicroservice.h"
#include "./yutil.h"

namespace ymicroservice {

using ydb::ConnectionInfo;
using ydb::ConnectionPool;
using ydb::Migration;
using ydb::MigrationsRunner;
using yutil::Env;
using yutil::ROTypeMap;

class DBCapability : public Capability {
 public:
  explicit DBCapability(const Env& env);

  ConnectionPool* connPool();

  DBCapability* registerMigration(Migration* migration);

  DBCapability* registerMigrations(const std::vector<Migration*>& migrations);

  void beforeStart(const ROTypeMap& capabilities) override;

 private:
  ConnectionInfo   connInfo;
  ConnectionPool   _connPool;
  MigrationsRunner migrationsRunner;
};

}  // namespace ymicroservice

#endif  // !YDBCAPABILITY_INCLUDE_DB_CAPABILITY_H_
