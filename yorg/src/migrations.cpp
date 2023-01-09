#include <vector>
#include "./migrations/2023-01-05T16-00-create-task.cpp"
#include "ydb.h"

namespace yorg {
namespace migrations {

using std::vector;
using ydb::ConnectionInfo;
using ydb::Migration;
using ydb::MigrationsRunnerOptions;

const vector<Migration*> MIGRATIONS{new CreateTaskMigration()};

void runMigrations(ConnectionInfo          connInfo,
                   ConnectionInfo          defaultConnInfo,
                   MigrationsRunnerOptions opts = MigrationsRunnerOptions()) {
  ydb::MigrationsRunner(connInfo, defaultConnInfo, opts)
      .registerMigrations(MIGRATIONS)
      .run();
}

}  // namespace migrations
}  // namespace yorg
