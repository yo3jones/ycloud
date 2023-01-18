#include "./service.h"
#include "yutil.h"

int main() {
  yutil::Env    env;
  yorg::Service service{env};

  service.start();

  return 0;
}
