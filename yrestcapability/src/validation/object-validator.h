#ifndef YRESTCAPABILITY_SRC_VALIDATION_OBJECT_VALIDATOR_H_
#define YRESTCAPABILITY_SRC_VALIDATION_OBJECT_VALIDATOR_H_
#include <string>
#include <unordered_map>
#include <vector>
#include "./validator.h"
#include "./value-validator.h"

namespace ymicroservice {
namespace validation {

using std::string;
using std::vector;

class ObjectValidator : public Validator {
 public:
  explicit ObjectValidator(Constraint constraint);
  ObjectValidator();

  ~ObjectValidator();

  ObjectValidator* field(string key, Validator* validator);

  bool validate(ValidationResult*         result,
                const vector<string>&     path,
                const crow::json::rvalue& value) const override;

 private:
  std::unordered_map<string, Validator*>* map;

 private:
  void validateChild(ValidationResult*         result,
                     const vector<string>&     parentPath,
                     const crow::json::rvalue& parentValue,
                     string                    childKey,
                     Validator*                childValidator) const;
};

}  // namespace validation
}  // namespace ymicroservice

#endif  // !YRESTCAPABILITY_SRC_VALIDATION_OBJECT_VALIDATOR_H_
