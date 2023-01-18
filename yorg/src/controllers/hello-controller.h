#ifndef YORG_SRC_CONTROLLERS_HELLO_CONTROLLER_H_
#define YORG_SRC_CONTROLLERS_HELLO_CONTROLLER_H_
#include <string>
#include "crow.h"

using std::string;

class HelloController {
 public:
  string get(const crow::request& request);
};

#endif  // !YORG_SRC_CONTROLLERS_HELLO_CONTROLLER_H_
