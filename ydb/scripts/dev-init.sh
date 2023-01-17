#!/bin/bash
set -e

# Copy example.env to .env if it doesn't exist
if [ ! -f .env ]
then
  cp example.env .env
fi
if [ ! -f test.env ]
then
  cp example.test.env test.env
fi

ln -f -s ../.clang-format .clang-format
ln -f -s ../CPPLINT.cfg CPPLINT.cfg

cmake -S ../ -B ../out/build
cmake --build ../out/build --target ydb ydb_test ydb_test_test

ln -s -f ../out/build/compile_commands.json compile_commands.json
