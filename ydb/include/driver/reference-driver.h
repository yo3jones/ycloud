#ifndef YDB_INCLUDE_DRIVER_REFERENCE_DRIVER_H_
#define YDB_INCLUDE_DRIVER_REFERENCE_DRIVER_H_
#include <string>

using std::string;

namespace ydb {
namespace driver {

class ReferenceDriver {
 public:
  virtual ~ReferenceDriver() = default;

  virtual bool   isNull()   = 0;
  virtual string asString() = 0;
  virtual int    asInt()    = 0;
};

}  // namespace driver
}  // namespace ydb

#endif  // !YDB_INCLUDE_DRIVER_REFERENCE_DRIVER_H_
