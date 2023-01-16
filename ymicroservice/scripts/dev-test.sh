#!/bin/bash
set -e

cmake --build out/build --target ymicroservice_test

echo
echo "====================="
echo

./out/build/ymicroservice_test $1
