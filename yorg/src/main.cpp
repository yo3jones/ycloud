#include "controllers/hello-controller.h"
#include "crow.h"
#include "crow/app.h"

int main() {
  crow::SimpleApp  app;
  HelloController  helloController;
  HelloController* hc = &helloController;

  CROW_ROUTE(app, "/hello")
  ([hc]() { return hc->get(); });

  app.port(8080).multithreaded().run();

  return 0;
}
