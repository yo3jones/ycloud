#ifndef YDB_INCLUDE_ROW_H_
#define YDB_INCLUDE_ROW_H_
#include <memory>
#include <string>
#include "./driver/row-driver.h"
#include "./reference.h"

using std::shared_ptr;
using std::string;

namespace ydb {

using driver::RowDriver;

class Row {
 public:
  explicit Row(RowDriver* rowDriver);

  Reference at(int i);
  Reference at(const string& column);
  Reference operator[](int i);
  Reference operator[](const string& column);

 private:
  shared_ptr<RowDriver> rowDriver;
};

}  // namespace ydb

#endif  // !YDB_INCLUDE_ROW_H_
