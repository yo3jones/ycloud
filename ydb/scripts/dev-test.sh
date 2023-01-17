#!/bin/bash
set -o allexport; source test.env; set +o allexport; set -e;

cmake --build ../out/build --target ydb_test_test

echo
echo "====================="
echo

../out/build/ydb/ydb_test_test $1
