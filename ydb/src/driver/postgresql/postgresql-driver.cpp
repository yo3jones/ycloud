#include "../../../include/driver/postgresql/postgresql-driver.h"
#include "../../../include/driver/postgresql/postgresql-result-driver.h"

using std::shared_ptr;

namespace ydb {
namespace driver {
namespace postgresql {

string PostgresqlDriver::buildConnectionString(
    const ConnectionInfo& connectionInfo) {
  return "postgresql://" + connectionInfo.getUser() + ":" +
         connectionInfo.getPassword() + "@" + connectionInfo.getHost() + "/" +
         connectionInfo.getDatabase();
}

PostgresqlDriver::PostgresqlDriver() : backingConnection() {}

void PostgresqlDriver::connect(const ConnectionInfo& connectionInfo) {
  backingConnection = shared_ptr<pqxx::connection>(
      new pqxx::connection(buildConnectionString(connectionInfo)));
}

void PostgresqlDriver::disconnect() {
  backingConnection->disconnect();
}

ResultDriver* PostgresqlDriver::exec(const string& query) {
  pqxx::nontransaction w{*backingConnection};

  pqxx::result backingResult = w.exec(query);

  return new PostgresqlResultDriver(backingResult);
}

}  // namespace postgresql
}  // namespace driver
}  // namespace ydb
