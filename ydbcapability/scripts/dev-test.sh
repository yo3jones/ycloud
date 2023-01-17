#!/bin/bash
set -o allexport; source test.env; set +o allexport; set -e;

cmake --build ../out/build --target ydbcapability_test

echo
echo "====================="
echo

../out/build/ydbcapability/ydbcapability_test $1
