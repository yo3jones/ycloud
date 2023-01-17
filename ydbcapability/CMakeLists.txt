cmake_minimum_required(VERSION 3.14)
project(ydbcapability)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

add_library(ydbcapability
  src/db-capability.cpp
)
target_include_directories(ydbcapability
  PUBLIC include
)
target_link_libraries(ydbcapability
  yutil
  ymicroservice
  ydb
)
add_dependencies(ydbcapability
  ymicroservice
  ydb
)

add_executable(ydbcapability_test
  # test/test-setup.cpp

  test/db-capability_test.cpp
)
target_link_libraries(ydbcapability_test
  ydbcapability
  ymicroservice_test
  GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(ydbcapability_test)
