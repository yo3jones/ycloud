#ifndef YORG_SRC_SERVICE_H_
#define YORG_SRC_SERVICE_H_
#include "./db-accessor.h"
#include "./middleware.h"
#include "./ydbrestcapability.h"
#include "./ymicroservice.h"
#include "./yutil.h"

#include "migrations/2023-01-05T16-00-create-task.cpp"  // NOLINT

#include "controllers/hello-controller.h"
#include "controllers/tasks-controller.h"

namespace yorg {

class Service {
 public:
  explicit Service(const yutil::Env& env);
  Service(const Service&) = delete;

  void start();

  ymicroservice::Service& getService();

 private:
  ymicroservice::Service                service;
  ymicroservice::DBAccessor<MIDDLEWARE> dbAccessor;

  migrations::CreateTaskMigration* createTaskMigration;

  HelloController              helloController;
  controllers::TasksController tasksController;
};

}  // namespace yorg

#endif  // !YORG_SRC_SERVICE_H_
