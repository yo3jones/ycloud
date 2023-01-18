#!/bin/bash

set -o allexport; source .env; set +o allexport; set -e

cmake --build ../out/build --target yorg

echo
echo "====================="
echo

../out/build/yorg/yorg
