#ifndef YDB_SRC_MIGRATIONS_RUNNER_H_
#define YDB_SRC_MIGRATIONS_RUNNER_H_
#include <string>
#include <vector>
#include "./connection-info.h"
#include "./migration.h"
#include "pqxx/pqxx"

namespace ydb {

using std::vector;

class MigrationsRunnerOptions {
 public:
  MigrationsRunnerOptions();

  MigrationsRunnerOptions& migrationTableName(const string& migrationTableName);

 private:
  std::string _migrationTableName;

  friend class MigrationsRunner;
};

class MigrationsRunner {
 public:
  explicit MigrationsRunner(
      ConnectionInfo          connInfo,
      ConnectionInfo          defaultConnInfo,
      MigrationsRunnerOptions opts = MigrationsRunnerOptions());
  ~MigrationsRunner();

  MigrationsRunner& registerMigration(Migration* migration);
  MigrationsRunner& registerMigrations(const vector<Migration*>& migrations);

  void run();

 private:
  enum RunMode { skip, insert, update };
  const string RUNNING  = "running";
  const string COMPLETE = "complete";
  const string ERROR    = "error";

  ConnectionInfo          connInfo;
  ConnectionInfo          defaultConnInfo;
  pqxx::connection*       conn;
  MigrationsRunnerOptions opts;
  vector<Migration*>      migrations;

  static bool compareMigrations(Migration* a, Migration* b);

  void initMigrationsTable();
  void runMigration(Migration* migration);
  bool startMigration(Migration* migration);
  void completeMigration(Migration* migration, const string& status);
};

}  // namespace ydb

#endif  // !YDB_SRC_MIGRATIONS_RUNNER_H_
