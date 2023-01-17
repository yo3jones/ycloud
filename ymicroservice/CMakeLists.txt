cmake_minimum_required(VERSION 3.14)
project(ymicroservice)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

add_library(ymicroservice
  src/capability.cpp
  src/service.cpp
  src/startable.cpp
)
target_include_directories(ymicroservice
  PUBLIC include
)
target_link_libraries(ymicroservice
  yutil
)

add_library(ymicroservice_test
  test/microservice-test-environment.cpp
)
target_include_directories(ymicroservice_test
  PUBLIC test/include
)
target_link_libraries(ymicroservice_test
  ymicroservice
  GTest::gtest_main
)

add_executable(ymicroservice_test_test
  test/service_test.cpp
)
target_link_libraries(ymicroservice_test_test
  ymicroservice_test
)
include(GoogleTest)
gtest_discover_tests(ymicroservice_test_test)
