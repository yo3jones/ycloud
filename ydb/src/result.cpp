#include "../include/result.h"
#include "../include/driver/result-driver.h"
#include "../include/row.h"

using ydb::Result;
using ydb::Row;

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
