#ifndef YDB_INCLUDE_DRIVER_ROW_DRIVER_H_
#define YDB_INCLUDE_DRIVER_ROW_DRIVER_H_
#include <string>
#include "./reference-driver.h"

using std::string;
using ydb::driver::ReferenceDriver;

namespace ydb {
namespace driver {

class RowDriver {
 public:
  virtual ~RowDriver() = default;

  virtual ReferenceDriver* at(int i)                = 0;
  virtual ReferenceDriver* at(const string& column) = 0;
};

}  // namespace driver
}  // namespace ydb

#endif  // !YDB_INCLUDE_DRIVER_ROW_DRIVER_H_
