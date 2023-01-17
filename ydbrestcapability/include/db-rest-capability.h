#ifndef YDBRESTCAPABILITY_INCLUDE_DB_REST_CAPABILITY_H_
#define YDBRESTCAPABILITY_INCLUDE_DB_REST_CAPABILITY_H_
#include "./crow.h"
#include "./db-accessor.h"
#include "./db-middleware.h"
#include "./ydbcapability.h"
#include "./ymicroservice.h"
#include "./yrestcapability.h"
#include "./yutil.h"

namespace ymicroservice {

using yutil::ROTypeMap;

template <typename... Middleware>
class DBRESTCapability : public Capability {
 public:
  void beforeStart(const ROTypeMap& capabilities) override {
    auto* restCapability = capabilities.get<RESTCapability<Middleware...>>();
    auto* dbCapability   = capabilities.get<DBCapability>();

    crow::App<Middleware...>& app      = restCapability->getApp();
    auto*                     connPool = dbCapability->connPool();

    auto& dbMiddleware = app.template get_middleware<DBMiddleware>();
    dbMiddleware.setConnectionPool(connPool);
  }
};

}  // namespace ymicroservice

#endif  // !YDBRESTCAPABILITY_INCLUDE_DB_REST_CAPABILITY_H_
