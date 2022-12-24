#include <iostream>
#include <pqxx/pqxx>

int main() {
  pqxx::connection c{"postgresql://root:password@localhost/default"};
  pqxx::work txn{c};
  txn.commit();
  c.disconnect();
  return 0;
}
