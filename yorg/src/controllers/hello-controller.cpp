#include "./hello-controller.h"

HelloController::HelloController(ConnAccessor& connAccessor)
    : connAccessor(connAccessor) {}

string HelloController::get(const crow::request& req) {
  return "hi there";
}
