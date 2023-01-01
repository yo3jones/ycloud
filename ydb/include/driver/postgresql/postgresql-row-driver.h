#include <string>
#include "../reference-driver.h"
#include "../row-driver.h"
#include "pqxx/pqxx"

using std::string;

namespace ydb {
namespace driver {
namespace postgresql {

class PostgresqlRowDriver : public RowDriver {
 public:
  explicit PostgresqlRowDriver(pqxx::row backingRow);

  ReferenceDriver* at(int i);
  ReferenceDriver* at(const string& column);

 private:
  pqxx::row backingRow;
};

}  // namespace postgresql
}  // namespace driver
}  // namespace ydb
