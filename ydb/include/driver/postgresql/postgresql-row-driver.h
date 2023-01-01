#include <string>
#include "../reference-driver.h"
#include "../row-driver.h"
#include "pqxx/pqxx"

using driver_ydb::ReferenceDriver;
using driver_ydb::RowDriver;
using std::string;

namespace postgresql_ydb {

class PostgresqlRowDriver : public RowDriver {
 public:
  explicit PostgresqlRowDriver(pqxx::row backingRow);

  ReferenceDriver* at(int i);
  ReferenceDriver* at(const string& column);

 private:
  pqxx::row backingRow;
};

}  // namespace postgresql_ydb
