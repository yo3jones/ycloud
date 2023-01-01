#include "../include/connection-info-builder.h"
#include "../include/connection-info.h"

using ydb::ConnectionInfo;
using ydb::ConnectionInfoBuilder;

ConnectionInfoBuilder::ConnectionInfoBuilder()
    : _type{Type::none},
      _host{""},
      _port{"5432"},
      _user{""},
      _password{""},
      _database{""} {}

ConnectionInfoBuilder::ConnectionInfoBuilder(ConnectionInfo connInfo)
    : _type{connInfo.getType()},
      _host{connInfo.getHost()},
      _port{connInfo.getPort()},
      _user{connInfo.getUser()},
      _password{connInfo.getPassword()},
      _database{connInfo.getDatabase()} {}

ConnectionInfoBuilder& ConnectionInfoBuilder::type(Type type) {
  _type = type;
  return *this;
}

ConnectionInfoBuilder& ConnectionInfoBuilder::host(string host) {
  _host = host;
  return *this;
}

ConnectionInfoBuilder& ConnectionInfoBuilder::port(string port) {
  _port = port;
  return *this;
}

ConnectionInfoBuilder& ConnectionInfoBuilder::user(string user) {
  _user = user;
  return *this;
}

ConnectionInfoBuilder& ConnectionInfoBuilder::password(string password) {
  _password = password;
  return *this;
}

ConnectionInfoBuilder& ConnectionInfoBuilder::database(string database) {
  _database = database;
  return *this;
}

ConnectionInfo ConnectionInfoBuilder::build() const {
  return ConnectionInfo(_type, _host, _port, _user, _password, _database);
}
