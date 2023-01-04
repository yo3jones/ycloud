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

  pqxx::result res = txn.exec_params("UPDATE " + opts._migrationTableName +
                                         " SET status=$1,"
                                         "     updated_at=current_timestamp"
                                         " WHERE name=$2"
                                         " AND status=$3",
                                     RUNNING, migration->name(), ERROR);

  if (res.affected_rows() > 0) {
    txn.commit();
    return true;
  }

  try {
    txn.exec_params("INSERT INTO " + opts._migrationTableName +
                        " (name, status) "
                        " VALUES ($1, $2)",
                    migration->name(), RUNNING);
  } catch (...) {
    txn.commit();
    return false;
  }

  txn.commit();

  return true;
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
