#ifndef YORG_SRC_MIGRATIONS_H_
#define YORG_SRC_MIGRATIONS_H_
#include <vector>
#include "ydb.h"

namespace yorg {
namespace migrations {

using std::vector;
using ydb::ConnectionInfo;
using ydb::Migration;

class Migrations {
 public:
  Migrations();

  const vector<Migration*>& get();

  void run(const ConnectionInfo& connInfo,
           const ConnectionInfo& defaultConnInfo);

 private:
  vector<Migration*> migrations;
};

}  // namespace migrations
}  // namespace yorg

#endif  // !YORG_SRC_MIGRATIONS_H_
