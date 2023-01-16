
#!/bin/bash
# set -o allexport; source .env; set +o allexport; set -e;

cmake --build out/build --target yrestcapability_test_test

echo
echo "====================="
echo

./out/build/yrestcapability_test_test $1
