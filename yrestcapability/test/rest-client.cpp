#include <ostream>
#include <string>

#include "crow/json.h"
#include "curlpp/Easy.hpp"
#include "curlpp/Options.hpp"
#include "curlpp/cURLpp.hpp"
#include "include/rest-client.h"

namespace ymicroservice {

RESTClient::RESTClient(const Env& env) : env(env) {}

crow::json::rvalue RESTClient::get(string path) {
  curlpp::Cleanup    cleanup;
  curlpp::Easy       req;
  std::ostringstream os;

  req.setOpt<curlpp::options::Url>(
      "http://localhost:" + std::to_string(env.httpPort()) + path);
  req.setOpt<curlpp::options::WriteStream>(&os);

  req.perform();

  return crow::json::load(os.str());
}

}  // namespace ymicroservice
