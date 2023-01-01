#include <string>

#include "../include/driver/reference-driver.h"
#include "../include/reference.h"

using driver_ydb::ReferenceDriver;
using std::string;
using ydb::Reference;

Reference::Reference(ReferenceDriver* referenceDriver)
    : referenceDriver(referenceDriver) {}

bool Reference::isNull() {
  return referenceDriver->isNull();
}

string Reference::asString() {
  return referenceDriver->asString();
}

int Reference::asInt() {
  return referenceDriver->asInt();
}
