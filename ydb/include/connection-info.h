#ifndef YDB_SRC_CONNECTION_INFO_H_
#define YDB_SRC_CONNECTION_INFO_H_
#include <string>

using std::string;

namespace ydb {

enum Type { none, postgresql };

class ConnectionInfo {
 public:
  ConnectionInfo();
  ConnectionInfo(Type   type,
                 string host,
                 string port,
                 string user,
                 string password,
                 string database);
  ConnectionInfo(const ConnectionInfo& connInfo);

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
};

}  // namespace ydb

#endif  // YDB_SRC_CONNECTION_INFO_H_
