#include "./server.h"
#include "yutil.h"

int main() {
  yorg::Server server{yutil::Env::PROD};
  server.start();
  return 0;
}
