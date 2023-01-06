#include "./migrations/2023-01-05T16-00-create-task.cpp"
#include "ydb.h"

namespace yorg {
namespace migrations {

using ydb::ConnectionInfo;
using ydb::Migration;
using ydb::MigrationsRunnerOptions;

const Migration* MIGRATIONS[]{new CreateTaskMigration()};
const size_t     MIGRATIONS_SIZE{sizeof(MIGRATIONS) / sizeof(ydb::Migration*)};

void runMigrations(ConnectionInfo          connInfo,
                   ConnectionInfo          defaultConnInfo,
                   MigrationsRunnerOptions opts = MigrationsRunnerOptions()) {
  ydb::MigrationsRunner(connInfo, defaultConnInfo, opts)
      .registerMigrations((Migration**)MIGRATIONS, 1)
      .run();
}

}  // namespace migrations
}  // namespace yorg
