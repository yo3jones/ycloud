#ifndef YUTIL_SRC_ENV_H_
#define YUTIL_SRC_ENV_H_
#include <string>

namespace yutil {

using std::string;

class Env {
 public:
  Env();

  string dbHost() const;
  string dbPort() const;
  string dbUser() const;
  string dbPassword() const;
  string dbDatabase() const;
  string dbDefaultDatabase() const;
  string dbTestDatabase() const;

 private:
  string _dbHost;
  string _dbPort;
  string _dbUser;
  string _dbPassword;
  string _dbDatabase;
  string _dbDefaultDatabase;
  string _dbTestDatabase;

  static string getEnv(const char* var, const string& defaultValue);
};

}  // namespace yutil

#endif  // !YUTIL_SRC_ENV_H_
