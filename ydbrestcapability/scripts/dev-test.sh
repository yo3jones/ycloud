#!/bin/bash
set -o allexport; source test.env; set +o allexport; set -e;

cmake --build ../out/build --target ydbrestcapability_test

echo
echo "====================="
echo

../out/build/ydbrestcapability/ydbrestcapability_test $1
