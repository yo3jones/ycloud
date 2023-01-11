#include "./migrations.h"
#include "./migrations/2023-01-05T16-00-create-task.cpp"

namespace yorg {
namespace migrations {

using ydb::ConnectionInfo;
using ydb::MigrationsRunnerOptions;

Migrations::Migrations() : migrations{new CreateTaskMigration} {}

const vector<Migration*>& Migrations::get() {
  return migrations;
}

void Migrations::run(const ConnectionInfo& connInfo,
                     const ConnectionInfo& defaultConnInfo) {
  ydb::MigrationsRunner(connInfo, defaultConnInfo)
      .registerMigrations(migrations)
      .run();
}

}  // namespace migrations
}  // namespace yorg
