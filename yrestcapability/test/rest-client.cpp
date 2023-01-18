#include <list>
#include <ostream>
#include <string>
#include <vector>

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

  req.setOpt<curlpp::options::Url>(buildURL(path));
  req.setOpt<curlpp::options::WriteStream>(&os);

  req.perform();

  return crow::json::load(os.str());
}

crow::json::rvalue RESTClient::post(string                    path,
                                    const crow::json::wvalue& value) {
  curlpp::Cleanup    cleanup;
  curlpp::Easy       req;
  std::ostringstream os;
  std::list<string>  headers{"Content-Type: application/json"};
  string             body = value.dump();

  req.setOpt<curlpp::options::Url>(buildURL(path));
  req.setOpt(new curlpp::options::HttpHeader(headers));
  req.setOpt(new curlpp::options::PostFields(body));
  req.setOpt(new curlpp::options::PostFieldSize(body.length()));
  req.setOpt(new curlpp::options::CustomRequest(("POST")));
  req.setOpt<curlpp::options::WriteStream>(&os);

  req.perform();

  return crow::json::load(os.str());
}

string RESTClient::buildURL(string path) {
  return "http://localhost:" + std::to_string(env.httpPort()) + path;
}

}  // namespace ymicroservice
