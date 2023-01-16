cmake_minimum_required(VERSION 3.14)
project(ydbcapability)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

# Avoid warning about DOWNLOAD_EXTRACT_TIMESTAMP in CMake 3.24:
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
  cmake_policy(SET CMP0135 NEW)
endif()

add_subdirectory(
  ../ydb
  ${CMAKE_CURRENT_BINARY_DIR}/ydb
)
add_subdirectory(
  ../ymicroservice
  ${CMAKE_CURRENT_BINARY_DIR}/ymicroservice
)

include(FetchContent)

# Google Test
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/58d77fa8070e8cec2dc1ed015d66b454c8d78850.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()

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
