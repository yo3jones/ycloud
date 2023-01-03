#ifndef YDB_INCLUDE_MIGRATION_H_
#define YDB_INCLUDE_MIGRATION_H_
#include <string>
#include "pqxx/pqxx"

namespace ydb {

class Migration {
 public:
  virtual void        up(pqxx::connection& conn);  // NOLINT
  virtual void        up(pqxx::work& txn);         // NOLINT
  virtual std::string name() = 0;
};

}  // namespace ydb

#endif  // !YDB_INCLUDE_MIGRATION_H_
