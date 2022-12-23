#! /bin/bash

cmake -S . -B build \
  && cmake --build build \
  && ln -s -f build/compile_commands.json compile_commands.json
