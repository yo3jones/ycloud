#include "../include/row.h"
#include "../include/driver/row-driver.h"
#include "../include/reference.h"

using driver_ydb::RowDriver;
using ydb::Reference;
using ydb::Row;

Row::Row(RowDriver* rowDriver) : rowDriver(rowDriver) {}

Reference Row::at(int i) {
  return Reference(rowDriver->at(i));
}

Reference Row::at(const string& column) {
  return Reference(rowDriver->at(column));
}

Reference Row::operator[](int i) {
  return at(i);
}

Reference Row::operator[](const string& column) {
  return at(column);
}
