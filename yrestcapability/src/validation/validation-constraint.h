#ifndef YRESTCAPABILITY_SRC_VALIDATION_VALIDATION_CONSTRAINT_H_
#define YRESTCAPABILITY_SRC_VALIDATION_VALIDATION_CONSTRAINT_H_

namespace ymicroservice {
namespace validation {

using Constraint = unsigned char;

const Constraint DEFAULT  = 0b0000'0000;  // OPTIONAL | STRICT | NOT_NULLABLE
const Constraint REQUIRED = 0b0000'0001;
const Constraint OPTIONAL = 0b0000'0000;
const Constraint LENIENT  = 0b0000'0010;
const Constraint STRICT   = 0b0000'0000;
const Constraint NULLABLE = 0b0000'0100;
const Constraint NOT_NULLABLE = 0b0000'0000;

bool isRequired(Constraint constraint);

bool isStrict(Constraint constraint);

bool isNullable(Constraint constraint);

}  // namespace validation
}  // namespace ymicroservice

#endif  // !YRESTCAPABILITY_SRC_VALIDATION_VALIDATION_CONSTRAINT_H_
