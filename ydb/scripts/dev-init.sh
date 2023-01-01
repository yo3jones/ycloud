#!/bin/bash
set -e

# Copy example.env to .env if it doesn't exist
if [ ! -f .env ]
then
  cp example.env .env
fi

ln -f -s ../.clang-format .clang-format
ln -f -s ../CPPLINT.cfg CPPLINT.cfg

cmake -S . -B out/build
cmake --build out/build

ln -s -f out/build/compile_commands.json compile_commands.json
