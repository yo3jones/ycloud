#! /bin/bash

# Copy example.env to .env if it doesn't exist
if [ ! -f .env ]
then
  cp example.env .env
fi

cmake -S . -B build \
  && cmake --build build \
  && ln -s -f build/compile_commands.json compile_commands.json
