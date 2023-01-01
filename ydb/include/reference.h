#ifndef YDB_INCLUDE_REFERENCE_H_
#define YDB_INCLUDE_REFERENCE_H_
#include <memory>
#include <string>
#include "./driver/reference-driver.h"

using std::shared_ptr;
using std::string;

namespace ydb {

using driver::ReferenceDriver;

class Reference {
 public:
  explicit Reference(ReferenceDriver* referenceDriver);

  bool   isNull();
  string asString();
  int    asInt();

 private:
  shared_ptr<ReferenceDriver> referenceDriver;
};

}  // namespace ydb

#endif  // !YDB_INCLUDE_REFERENCE_H_
