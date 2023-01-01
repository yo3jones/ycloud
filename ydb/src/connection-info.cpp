#include "../include/connection-info.h"

using ydb::ConnectionInfo;
using ydb::Type;

ConnectionInfo::ConnectionInfo(Type   type,
                               string host,
                               string port,
                               string user,
                               string password,
                               string database) {
  this->type     = type;
  this->host     = host;
  this->port     = port;
  this->user     = user;
  this->password = password;
  this->database = database;
}

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
