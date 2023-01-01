#include <ydb.h>
#include <iostream>
// #include <pqxx/pqxx>

using ydb::ConnectionInfoBuilder;

int main() {
  // pqxx::connection c{"postgresql://root:password@localhost/default"};
  // pqxx::work txn{c};
  // txn.commit();
  // c.disconnect();

  auto connectionInfo = ConnectionInfoBuilder{}
                            .host("localhost")
                            .port("5432")
                            .user("root")
                            .password("password")
                            .database("default")
                            .build();

  std::cout << connectionInfo.getHost() << std::endl;

  return 0;
}
