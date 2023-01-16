#include "./connection-info.h"

namespace ydb {

const bool ConnectionInfo::USE_DEFAULT_DATABASE = true;

string ConnectionInfo::getDatabaseForEnv(const yutil::Env& env,
                                         bool              useDefaultDatabase) {
  return useDefaultDatabase ? env.dbDefaultDatabase() : env.dbDatabase();
}

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

ConnectionInfo::ConnectionInfo(const yutil::Env& env, bool useDefaultDatabase)
    : type(Type::postgresql),
      host(env.dbHost()),
      port(env.dbPort()),
      user(env.dbUser()),
      password(env.dbPassword()),
      database(getDatabaseForEnv(env, useDefaultDatabase)) {}

Type ConnectionInfo::getType() const {
  return type;
}

string ConnectionInfo::getHost() const {
  return host;
}

string ConnectionInfo::getPort() const {
  return port;
}

string ConnectionInfo::getUser() const {
  return user;
}

string ConnectionInfo::getPassword() const {
  return password;
}

string ConnectionInfo::getDatabase() const {
  return database;
}

string ConnectionInfo::toURI() const {
  return "postgresql://" + user + ":" + password + "@" + host + ":" + port +
         "/" + database;
}

}  // namespace ydb
