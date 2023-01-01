#ifndef YDB_INCLUDE_DRIVER_DRIVER_FACTORY_H_
#define YDB_INCLUDE_DRIVER_DRIVER_FACTORY_H_

#include "./driver.h"

namespace ydb {
namespace driver {

class DriverFactory {
 public:
  virtual Driver* create() const = 0;
};

}  // namespace driver
}  // namespace ydb

#endif  // !YDB_INCLUDE_DRIVER_DRIVER_FACTORY_H_
