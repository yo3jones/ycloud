#ifndef YDB_SRC_CONNECTION_INFO_BUILDER_H_
#define YDB_SRC_CONNECTION_INFO_BUILDER_H_

#include <string>
#include "./connection-info.h"

using std::string;

namespace ydb {

class ConnectionInfoBuilder {
 public:
  ConnectionInfoBuilder();

  explicit ConnectionInfoBuilder(ConnectionInfo connInfo);

  ConnectionInfoBuilder& type(Type type);

  ConnectionInfoBuilder& host(string host);

  ConnectionInfoBuilder& port(string port);

  ConnectionInfoBuilder& user(string user);

  ConnectionInfoBuilder& password(string password);

  ConnectionInfoBuilder& database(string database);

  ConnectionInfo build() const;

 private:
  Type   _type;
  string _host;
  string _port;
  string _user;
  string _password;
  string _database;
};

}  // namespace ydb

#endif  // YDB_SRC_CONNECTION_INFO_BUILDER_H_
