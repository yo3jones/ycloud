#!/bin/bash
set -e

# Copy example.env to .env if it doesn't exist
# if [ ! -f .env ]
# then
#   cp example.env .env
# fi

ln -f -s ../.clang-format .clang-format
ln -f -s ../CPPLINT.cfg CPPLINT.cfg

# initialize the cmake project
cmake -S ../ -B ../out/build

# run the cmake build
cmake \
  --build ../out/build \
  --target ymicroservice ymicroservice_test ymicroservice_test_test

# sym link compile_commands.json for ide
ln -s -f ../out/build/compile_commands.json compile_commands.json
