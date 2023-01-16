#ifndef YRESTCAPABILITY_INCLUDE_REST_CAPABILITY_H_
#define YRESTCAPABILITY_INCLUDE_REST_CAPABILITY_H_
#include "./crow.h"
#include "./ymicroservice.h"
#include "./yutil.h"
#include "crow/app.h"

namespace ymicroservice {

using yutil::Env;

template <typename... Middleware>
class RESTCapability : public Capability, public Startable {
 public:
  explicit RESTCapability(const Env& env) : env(env), app() {}

  void start() override { app.port(env.httpPort()).multithreaded().run(); }

  void stop() override { app.stop(); }

  void waitForStart() override { app.wait_for_server_start(); }

  crow::App<Middleware...>& getApp() { return app; }

 private:
  const Env&               env;
  crow::App<Middleware...> app;
};

}  // namespace ymicroservice

#endif  // !YRESTCAPABILITY_INCLUDE_REST_CAPABILITY_H_
