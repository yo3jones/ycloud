#!/bin/bash
set -e

cmake --build ../out/build --target ymicroservice_test_test

echo
echo "====================="
echo

../out/build/ymicroservice/ymicroservice_test_test $1
