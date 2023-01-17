#!/bin/bash
set -e

cmake --build ../out/build --target yutil_test

echo
echo "====================="
echo

../out/build/yutil/yutil_test $1
