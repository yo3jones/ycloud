#ifndef YUTIL_SRC_ENV_H_
#define YUTIL_SRC_ENV_H_
#include <string>

namespace yutil {

using std::string;

class Env {
 public:
  Env();

  string dbHost();
  string dbPort();
  string dbUser();
  string dbPassword();
  string dbDatabase();
  string dbDefaultDatabase();
  string dbTestDatabase();

 private:
  string _dbHost;
  string _dbPort;
  string _dbUser;
  string _dbPassword;
  string _dbDatabase;
  string _dbDefaultDatabase;
  string _dbTestDatabase;
};

}  // namespace yutil

#endif  // !YUTIL_SRC_ENV_H_
