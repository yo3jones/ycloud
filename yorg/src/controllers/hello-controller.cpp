#include "./hello-controller.h"

string HelloController::get(const crow::request& req) {
  return "hi there";
}
