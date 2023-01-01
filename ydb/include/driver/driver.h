#ifndef YDB_INCLUDE_DRIVER_DRIVER_H_
#define YDB_INCLUDE_DRIVER_DRIVER_H_
#include <string>
#include "../connection-info.h"
#include "./result-driver.h"

using std::string;
using ydb::ConnectionInfo;

namespace ydb {
namespace driver {

class Driver {
 public:
  virtual ~Driver() = default;

  virtual void connect(const ConnectionInfo& connectionInfo) = 0;
  virtual void disconnect()                                  = 0;

  virtual ResultDriver* exec(const string& query) = 0;
};

}  // namespace driver
}  // namespace ydb

#endif  // !YDB_INCLUDE_DRIVER_DRIVER_H_
