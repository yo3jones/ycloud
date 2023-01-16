#ifndef YUTIL_SRC_ENV_H_
#define YUTIL_SRC_ENV_H_
#include <string>

namespace yutil {

using std::string;

class Env {
 public:
  enum EnvType { DEV, TEST, PROD };

  Env();

  int httpPort() const;

  string dbHost() const;
  string dbPort() const;
  string dbUser() const;
  string dbPassword() const;
  string dbDatabase() const;
  string dbDefaultDatabase() const;
  int    dbPoolSize() const;

 private:
  int _httpPort;

  string _dbHost;
  string _dbPort;
  string _dbUser;
  string _dbPassword;
  string _dbDatabase;
  string _dbDefaultDatabase;
  int    _dbPoolSize;

  static string getEnv(const char* var, const string& defaultValue);
  static int    getIntEnv(const char* var, const string& defaultValue);
};

}  // namespace yutil

#endif  // !YUTIL_SRC_ENV_H_
