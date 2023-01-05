#!/bin/bash
set -e

# Copy example.env to .env if it doesn't exist
if [ ! -f .env ]
then
  cp example.env .env
fi

ln -f -s ../.clang-format .clang-format
ln -f -s ../CPPLINT.cfg CPPLINT.cfg

# make sure the dep dir is created
mkdir -p out/deps

# link the ydb dependency library
ln -s -f ../../../ydb out/deps/ydb

# initialize the cmake project
cmake -S . -B out/build

# run the cmake build
cmake --build out/build

# sym link compile_commands.json for ide
ln -s -f out/build/compile_commands.json compile_commands.json
