#ifndef YDB_SRC_CONNECTION_INFO_H_
#define YDB_SRC_CONNECTION_INFO_H_
#include <string>
#include "./yutil.h"

using std::string;

namespace ydb {

enum Type { none, postgresql };

class ConnectionInfo {
 public:
  enum DBNameType { MAIN, DEFAULT, TEST };

  ConnectionInfo();
  ConnectionInfo(Type   type,
                 string host,
                 string port,
                 string user,
                 string password,
                 string database);
  ConnectionInfo(const ConnectionInfo& connInfo);
  explicit ConnectionInfo(const yutil::Env& env, DBNameType dbNameType);

  Type getType() const;

  string getHost() const;

  string getPort() const;

  string getUser() const;

  string getPassword() const;

  string getDatabase() const;

  string toURI() const;

 private:
  Type   type;
  string host;
  string port;
  string user;
  string password;
  string database;

  static string getDatabaseForEnv(const yutil::Env& env, DBNameType envType);
};

}  // namespace ydb

#endif  // YDB_SRC_CONNECTION_INFO_H_
