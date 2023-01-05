#!/bin/bash
set -e

cmake --build out/build --target yutil_test

echo
echo "====================="
echo

./out/build/yutil_test $1
