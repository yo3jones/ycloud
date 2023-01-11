#include "./connection-info.h"

namespace ydb {

string ConnectionInfo::getDatabaseForEnv(const yutil::Env& env,
                                         DBNameType        dbNameType) {
  switch (dbNameType) {
    case DBNameType::MAIN:
      return env.dbDatabase();
    case DBNameType::DEFAULT:
      return env.dbDefaultDatabase();
    case DBNameType::TEST:
      return env.dbTestDatabase();
  }
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

ConnectionInfo::ConnectionInfo(const yutil::Env& env, DBNameType envType)
    : type(Type::postgresql),
      host(env.dbHost()),
      port(env.dbPort()),
      user(env.dbUser()),
      password(env.dbPassword()),
      database(getDatabaseForEnv(env, envType)) {}

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
