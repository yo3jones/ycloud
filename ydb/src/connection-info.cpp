#include "./connection-info.h"

namespace ydb {

ConnectionInfo::ConnectionInfo()
    : type(Type::none),
      host(""),
      port(""),
      user(""),
      password(""),
      database("") {}

ConnectionInfo::ConnectionInfo(Type   type,
                               string host,
                               string port,
                               string user,
                               string password,
                               string database)
    : type(type),
      host(host),
      port(port),
      user(user),
      password(password),
      database(database) {}

ConnectionInfo::ConnectionInfo(const ConnectionInfo& connInfo)
    : type(connInfo.type),
      host(connInfo.host),
      port(connInfo.port),
      user(connInfo.user),
      password(connInfo.password),
      database(connInfo.database) {}

Type ConnectionInfo::getType() const {
  return type;
}

string ConnectionInfo::getHost() const {
  return this->host;
}

string ConnectionInfo::getPort() const {
  return this->port;
}

string ConnectionInfo::getUser() const {
  return this->user;
}

string ConnectionInfo::getPassword() const {
  return this->password;
}

string ConnectionInfo::getDatabase() const {
  return this->database;
}

string ConnectionInfo::toURI() const {
  return "postgresql://" + user + ":" + password + "@" + host + ":" + port +
         "/" + database;
}

}  // namespace ydb
