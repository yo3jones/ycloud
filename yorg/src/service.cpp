#include "./service.h"
#include "./crow.h"
#include "./db-rest-capability.h"
#include "./rest-capability.h"
#include "./ydbcapability.h"
#include "./yrestcapability.h"

namespace yorg {

using ymicroservice::DBCapability;
using ymicroservice::DBMiddleware;
using ymicroservice::DBRESTCapability;
using ymicroservice::RESTCapability;

Service::Service(const yutil::Env& env)
    : service(),
      dbAccessor(),

      createTaskMigration(new migrations::CreateTaskMigration()),

      helloController(),
      tasksController(dbAccessor) {
  service.addCapability(new DBCapability(env, createTaskMigration))
      .addCapability(new RESTCapability<MIDDLEWARE>(env))
      .addCapability(new DBRESTCapability<MIDDLEWARE>);

  auto& app = service.getCapability<RESTCapability<MIDDLEWARE>>()->getApp();

  CROW_ROUTE(app, "/hello")
      .methods(crow::HTTPMethod::GET)([this](const crow::request& req) {
        return helloController.get(req);
      });

  CROW_ROUTE(app, "/users/<string>/tasks")
      .methods(crow::HTTPMethod::POST)(
          [this](const crow::request& req, string userId) {
            return tasksController.post(req);
          });

  CROW_ROUTE(app, "/users/<string>/tasks")
      .methods(crow::HTTPMethod::GET)(
          [this](const crow::request& req, string userId) {
            return tasksController.get(req);
          });
}

void Service::start() {
  service.start();
}

ymicroservice::Service& Service::getService() {
  return service;
}

}  // namespace yorg
