#include <string>
#include "ydb.h"

namespace yorg {
namespace migrations {

class CreateTaskMigration : public ydb::Migration {
 public:
  string name() override { return "2023-01-05T16-00-create-task"; }

  void up(pqxx::work& txn) override {
    txn.exec(R"sql(
      CREATE TABLE task (
        id         uuid          PRIMARY KEY                          ,
        name       varchar(1000) NOT NULL                             ,
        updated_at timestamp     NOT NULL    DEFAULT current_timestamp,
        created_at timestamp     NOT NULL    DEFAULT current_timestamp
      )
    )sql");
  }
};

}  // namespace migrations
}  // namespace yorg
