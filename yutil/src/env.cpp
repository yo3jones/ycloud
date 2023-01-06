#include "./env.h"
#include <cstdlib>

namespace yutil {

string Env::getEnv(const char* var, const string& defaultValue) {
  char* value = getenv(var);
  if (value == nullptr) {
    return defaultValue;
  }
  return value;
}

Env::Env()
    : _dbHost(getEnv("DB_HOST", "localhost")),
      _dbPort(getEnv("DB_PORT", "5432")),
      _dbUser(getEnv("DB_USER", "root")),
      _dbPassword(getEnv("DB_PASSWORD", "password")),
      _dbDatabase(getEnv("DB_DATABASE", "")),
      _dbDefaultDatabase(getEnv("DB_DEFAULT_DATABASE", "default")),
      _dbTestDatabase(getEnv("DB_TEST_DATABASE", "")) {}

string Env::dbHost() const {
  return _dbHost;
}
string Env::dbPort() const {
  return _dbPort;
}
string Env::dbUser() const {
  return _dbUser;
}
string Env::dbPassword() const {
  return _dbPassword;
}
string Env::dbDatabase() const {
  return _dbDatabase;
}
string Env::dbDefaultDatabase() const {
  return _dbDefaultDatabase;
}
string Env::dbTestDatabase() const {
  return _dbTestDatabase;
}

}  // namespace yutil
