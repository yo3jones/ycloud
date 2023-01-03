#include <algorithm>
#include <exception>
#include <string>

#include "./migrations-runner.h"

namespace ydb {

MigrationsRunnerOptions::MigrationsRunnerOptions()
    : _migrationTableName("migrations") {}

MigrationsRunnerOptions& MigrationsRunnerOptions::migrationTableName(
    const string& migrationTableName) {
  _migrationTableName = migrationTableName;
  return *this;
}

MigrationsRunner::MigrationsRunner(ConnectionInfo          connInfo,
                                   MigrationsRunnerOptions opts)
    : conn(connInfo.toURI()), migrations(), opts(opts) {}

MigrationsRunner::~MigrationsRunner() {
  conn.close();
}

MigrationsRunner& MigrationsRunner::registerMigration(Migration* migration) {
  migrations.push_back(migration);
  return *this;
}

void MigrationsRunner::run() {
  initMigrationsTable();

  std::sort(migrations.begin(), migrations.end(), compareMigrations);

  for (Migration* migration : migrations) {
    runMigration(migration);
  }
}

bool MigrationsRunner::compareMigrations(Migration* a, Migration* b) {
  return a->name() <= b->name();
}

void MigrationsRunner::initMigrationsTable() {
  pqxx::work txn{conn};
  txn.exec("CREATE TABLE IF NOT EXISTS " + opts._migrationTableName +
           " "
           "("
           "  name       varchar(256) PRIMARY KEY, "
           "  status     varchar(256) NOT NULL, "
           "  updated_at timestamp    NOT NULL DEFAULT current_timestamp, "
           "  created_at timestamp    NOT NULL DEFAULT current_timestamp"
           ")");
  txn.commit();
}

void MigrationsRunner::runMigration(Migration* migration) {
  if (!startMigration(migration)) {
    return;
  }

  try {
    migration->up(conn);
    completeMigration(migration, COMPLETE);
  } catch (...) {
    completeMigration(migration, ERROR);
    throw;
  }
}

bool MigrationsRunner::startMigration(Migration* migration) {
  pqxx::work txn{conn};

  RunMode runMode = shouldRunMigration(migration, txn);

  if (runMode == RunMode::skip) {
    return false;
  }

  if (runMode == RunMode::insert) {
    txn.exec_params("INSERT INTO " + opts._migrationTableName +
                        " "
                        "(name, status) VALUES ($1, $2)",
                    migration->name(), RUNNING);
  } else {
    txn.exec_params("UPDATE " + opts._migrationTableName +
                        " "
                        "SET status=$2, "
                        "    updated_at=current_timestamp "
                        "WHERE name=$1 ",
                    migration->name(), RUNNING);
  }

  try {
    txn.commit();
  } catch (...) {
    // this means another process is running the migration
    return false;
  }

  return true;
}

MigrationsRunner::RunMode MigrationsRunner::shouldRunMigration(
    Migration*  migration,
    pqxx::work& txn) {
  pqxx::result res = txn.exec_params(
      "SELECT status FROM " + opts._migrationTableName + " WHERE name=$1",
      migration->name());

  if (res.empty()) {
    return RunMode::insert;
  }

  string status = res[0]["status"].c_str();

  return status == ERROR ? RunMode::update : RunMode::skip;
}

void MigrationsRunner::completeMigration(Migration*    migration,
                                         const string& status) {
  pqxx::work txn{conn};

  txn.exec_params("UPDATE " + opts._migrationTableName +
                      " "
                      "SET status=$2, "
                      "    updated_at=current_timestamp "
                      "WHERE name=$1 ",
                  migration->name(), status);
  txn.commit();
}

}  // namespace ydb
