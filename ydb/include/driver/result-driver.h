#ifndef YDB_INCLUDE_DIRVER_RESULT_DRIVER_H_
#define YDB_INCLUDE_DIRVER_RESULT_DRIVER_H_
#include "./row-driver.h"

namespace ydb {
namespace driver {

class ResultDriver {
 public:
  virtual ~ResultDriver() = default;

  virtual int        getRowCount() = 0;
  virtual RowDriver* at(int i)     = 0;
};

}  // namespace driver
}  // namespace ydb

#endif  // !YDB_INCLUDE_DIRVER_RESULT_DRIVER_H_
