#! /bin/bash

set -o allexport; source .env; set +o allexport

cmake --build build --target yorg \
  && echo  \
  && echo "=====================" \
  && echo  \
  && ./build/yorg
