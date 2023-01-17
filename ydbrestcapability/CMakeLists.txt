cmake_minimum_required(VERSION 3.14)
project(ydbrestcapability)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

add_library(ydbrestcapability
  src/db-accessor.cpp
  src/db-middleware.cpp
  src/db-rest-capability.cpp
)
target_include_directories(ydbrestcapability
  PUBLIC include
)
target_link_libraries(ydbrestcapability
  ymicroservice
  ydbcapability
  yrestcapability
)

add_executable(ydbrestcapability_test
  test/test-setup.cpp

  test/db-rest-capability_test.cpp
)
target_link_libraries(ydbrestcapability_test
  ydbrestcapability
  ymicroservice_test
  yrestcapability_test
  GTest::gtest
)
include(GoogleTest)
gtest_discover_tests(ydbrestcapability_test)
