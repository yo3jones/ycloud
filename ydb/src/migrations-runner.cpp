#include <algorithm>
#include <exception>
#include <string>

#include "./migrations-runner.h"
#include "./ydb.h"

namespace ydb {

MigrationsRunnerOptions::MigrationsRunnerOptions()
    : _migrationTableName("migrations") {}

MigrationsRunnerOptions& MigrationsRunnerOptions::migrationTableName(
    const string& migrationTableName) {
  _migrationTableName = migrationTableName;
  return *this;
}

MigrationsRunner::MigrationsRunner(ConnectionInfo          connInfo,
                                   ConnectionInfo          defaultConnInfo,
                                   MigrationsRunnerOptions opts)
    : connInfo(connInfo),
      defaultConnInfo(defaultConnInfo),
      conn(nullptr),
      migrations(),
      opts(opts) {}

MigrationsRunner::~MigrationsRunner() {
  for (Migration* migration : migrations) {
    delete migration;
  }
  if (conn != nullptr) {
    conn->close();
    delete conn;
  }
}

MigrationsRunner& MigrationsRunner::registerMigration(Migration* migration) {
  migrations.push_back(migration);
  return *this;
}

MigrationsRunner& MigrationsRunner::registerMigrations(Migration* migrations[],
                                                       size_t     size) {
  for (int i = 0; i < size; i++) {
    auto migration = migrations[i];
    registerMigration(migration);
  }

  return *this;
}

void MigrationsRunner::run() {
  createDatabase(defaultConnInfo, connInfo.getDatabase());

  conn = new pqxx::connection{connInfo.toURI()};

  initMigrationsTable();

  std::sort(migrations.begin(), migrations.end(), compareMigrations);

  for (Migration* migration : migrations) {
    runMigration(migration);
  }

  conn->close();
}

bool MigrationsRunner::compareMigrations(Migration* a, Migration* b) {
  return a->name() <= b->name();
}

void MigrationsRunner::initMigrationsTable() {
  pqxx::work txn{*conn};
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
    migration->up(*conn);
    completeMigration(migration, COMPLETE);
  } catch (...) {
    completeMigration(migration, ERROR);
    throw;
  }
}

bool MigrationsRunner::startMigration(Migration* migration) {
  pqxx::work txn{*conn};

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
  pqxx::work txn{*conn};

  txn.exec_params("UPDATE " + opts._migrationTableName +
                      " "
                      "SET status=$2, "
                      "    updated_at=current_timestamp "
                      "WHERE name=$1 ",
                  migration->name(), status);
  txn.commit();
}

}  // namespace ydb
