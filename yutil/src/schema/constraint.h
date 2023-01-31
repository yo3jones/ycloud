#ifndef YUTIL_SRC_SCHEMA_CONSTRAINT_H_
#define YUTIL_SRC_SCHEMA_CONSTRAINT_H_

namespace yutil {
namespace schema {

using Constraint = unsigned char;

const Constraint DEFALT       = 0b0000'0000;  // OPTIONAL | LENIENT | NULLABLE
const Constraint OPTIONAL     = 0b0000'0000;
const Constraint REQIRED      = 0b0000'0001;
const Constraint LENIENT      = 0b0000'0000;
const Constraint STRICT       = 0b0000'0010;
const Constraint NULLABLE     = 0b0000'0000;
const Constraint NOT_NULLABLE = 0b0000'0100;

bool isRequired(Constraint constraint);
bool isOptional(Constraint constraint);
bool isLenient(Constraint constraint);
bool isStrict(Constraint constraint);
bool isNullable(Constraint constraint);
bool isNotNullable(Constraint constraint);

}  // namespace schema
}  // namespace yutil

#endif  // !YUTIL_SRC_SCHEMA_CONSTRAINT_H_
