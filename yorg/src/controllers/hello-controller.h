#ifndef YORG_SRC_CONTROLLERS_HELLO_CONTROLLER_H_
#define YORG_SRC_CONTROLLERS_HELLO_CONTROLLER_H_
#include <string>
#include "../conn-accessor.h"
#include "../middleware/db-middleware.h"
#include "crow.h"

using std::string;
using yorg::ConnAccessor;

class HelloController {
 public:
  HelloController(ConnAccessor& connAccessor);
  string get(const crow::request& request);

 private:
  ConnAccessor& connAccessor;
};

#endif  // !YORG_SRC_CONTROLLERS_HELLO_CONTROLLER_H_
