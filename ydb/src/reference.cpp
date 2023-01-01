#include "../include/reference.h"

namespace ydb {

using driver::ReferenceDriver;

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

}  // namespace ydb
