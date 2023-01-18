#ifndef YRESTCAPABILITY_TEST_INCLUDE_REST_CLIENT_H_
#define YRESTCAPABILITY_TEST_INCLUDE_REST_CLIENT_H_
#include <string>
#include "./crow.h"
#include "./yutil.h"
#include "crow/json.h"

namespace ymicroservice {

using std::string;
using yutil::Env;

class RESTClient {
 public:
  explicit RESTClient(const Env& env);

  crow::json::rvalue get(string path);

  crow::json::rvalue post(string path, const crow::json::wvalue& value);

 private:
  const Env& env;

  string buildURL(string path);
};

}  // namespace ymicroservice

#endif  // !YRESTCAPABILITY_TEST_INCLUDE_REST_CLIENT_H_
