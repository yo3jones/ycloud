#ifndef YDB_INCLUDE_DRIVER_DRIVER_FACTORY_H_
#define YDB_INCLUDE_DRIVER_DRIVER_FACTORY_H_

#include "./driver.h"

using driver_ydb::Driver;

namespace driver_ydb {

class DriverFactory {
 public:
  virtual Driver* create() const = 0;
};

}  // namespace driver_ydb

#endif  // !YDB_INCLUDE_DRIVER_DRIVER_FACTORY_H_
