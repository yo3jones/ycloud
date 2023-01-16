#ifndef YMICROSERVICE_INCLUDE_CAPABILITIES_H_
#define YMICROSERVICE_INCLUDE_CAPABILITIES_H_

namespace ymicroservice {

class Capabilities {
 public:
  template <class C>
  C* getCapability() const;
};

}  // namespace ymicroservice

#endif  // !YMICROSERVICE_INCLUDE_CAPABILITIES_H_
