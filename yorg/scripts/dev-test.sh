#!/bin/bash
set -o allexport; source test.env; set +o allexport; set -e;

cmake --build ../out/build --target yorg_test

echo
echo "====================="
echo

../out/build/yorg/yorg_test $1
