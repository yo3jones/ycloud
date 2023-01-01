#!/bin/bash
set -o allexport; source .env; set +o allexport; set -e;

cmake --build out/build --target yorg_test

echo
echo "====================="
echo

./out/build/yorg_test
