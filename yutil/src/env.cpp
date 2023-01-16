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

int Env::getIntEnv(const char* var, const string& defaultValue) {
  return std::stoi(getEnv(var, defaultValue));
}

Env::Env()
    : _httpPort(getIntEnv("HTTP_PORT", "8080")),
      _dbHost(getEnv("DB_HOST", "localhost")),
      _dbPort(getEnv("DB_PORT", "5432")),
      _dbUser(getEnv("DB_USER", "root")),
      _dbPassword(getEnv("DB_PASSWORD", "password")),
      _dbDatabase(getEnv("DB_DATABASE", "")),
      _dbDefaultDatabase(getEnv("DB_DEFAULT_DATABASE", "default")),
      _dbPoolSize(getIntEnv("DB_POOL_SIZE", "10")) {}

int Env::httpPort() const {
  return _httpPort;
}

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

int Env::dbPoolSize() const {
  return _dbPoolSize;
}

}  // namespace yutil
