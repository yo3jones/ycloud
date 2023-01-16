#ifndef YMICROSERVICE_INCLUDE_STARTABLE_H_
#define YMICROSERVICE_INCLUDE_STARTABLE_H_

namespace ymicroservice {

class Startable {
 public:
  virtual void start() = 0;

  virtual void stop() = 0;

  virtual void waitForStart();
};

}  // namespace ymicroservice

#endif  // !YMICROSERVICE_INCLUDE_STARTABLE_H_
