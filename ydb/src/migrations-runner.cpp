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
      migrations(),
      opts(opts) {}

MigrationsRunner::~MigrationsRunner() {
  for (Migration* migration : migrations) {
    delete migration;
  }
}

MigrationsRunner& MigrationsRunner::registerMigration(Migration* migration) {
  migrations.push_back(migration);
  return *this;
}

MigrationsRunner& MigrationsRunner::registerMigrations(
    const vector<Migration*>& migrations) {
  for (Migration* migration : migrations) {
    registerMigration(migration);
  }

  return *this;
}

void MigrationsRunner::run() {
  createDatabase(defaultConnInfo, connInfo.getDatabase());

  pqxx::connection conn{connInfo.toURI()};

  initMigrationsTable(conn);

  std::sort(migrations.begin(), migrations.end(), compareMigrations);

  for (Migration* migration : migrations) {
    runMigration(conn, migration);
  }

  conn.close();
}

bool MigrationsRunner::compareMigrations(Migration* a, Migration* b) {
  return a->name() <= b->name();
}

void MigrationsRunner::initMigrationsTable(pqxx::connection& conn) {
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

void MigrationsRunner::runMigration(pqxx::connection& conn,
                                    Migration*        migration) {
  if (!startMigration(conn, migration)) {
    return;
  }

  try {
    migration->up(conn);
    completeMigration(conn, migration, COMPLETE);
  } catch (...) {
    completeMigration(conn, migration, ERROR);
    throw;
  }
}

bool MigrationsRunner::startMigration(pqxx::connection& conn,
                                      Migration*        migration) {
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

void MigrationsRunner::completeMigration(pqxx::connection& conn,
                                         Migration*        migration,
                                         const string&     status) {
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
