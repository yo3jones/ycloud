#include "./env.h"

namespace yutil {

Env::Env()
    : _dbHost(getenv("DB_HOST")),
      _dbPort(getenv("DB_PORT")),
      _dbUser(getenv("DB_USER")),
      _dbPassword(getenv("DB_PASSWORD")),
      _dbDatabase(getenv("DB_DATABASE")),
      _dbDefaultDatabase(getenv("DB_DEFAUTT_DATABASE")),
      _dbTestDatabase(getenv("DB_TEST_DATABASE")) {}

string Env::dbHost() {
  return _dbHost;
}
string Env::dbPort() {
  return _dbPort;
}
string Env::dbUser() {
  return _dbUser;
}
string Env::dbPassword() {
  return _dbPassword;
}
string Env::dbDatabase() {
  return _dbDatabase;
}
string Env::dbDefaultDatabase() {
  return _dbDefaultDatabase;
}
string Env::dbTestDatabase() {
  return _dbTestDatabase;
}

}  // namespace yutil
