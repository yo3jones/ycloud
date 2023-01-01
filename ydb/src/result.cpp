#include "../include/result.h"

namespace ydb {

Result::Result(ResultDriver* resultDriver) : resultDriver(resultDriver) {}

int Result::getRowCount() {
  return resultDriver->getRowCount();
}

Row Result::operator[](int i) {
  return at(i);
}

Row Result::at(int i) {
  return Row(resultDriver->at(i));
}

}  // namespace ydb
