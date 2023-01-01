#ifndef YDB_INCLUDE_RESULT_H_
#define YDB_INCLUDE_RESULT_H_
#include <memory>
#include "./driver/result-driver.h"
#include "./row.h"

using driver_ydb::ResultDriver;
using std::shared_ptr;

namespace ydb {

class Result {
 public:
  explicit Result(ResultDriver* resultDriver);

  int getRowCount();
  Row operator[](int i);
  Row at(int i);

 private:
  shared_ptr<ResultDriver> resultDriver;
};

}  // namespace ydb

#endif  // !YDB_INCLUDE_RESULT_H_
