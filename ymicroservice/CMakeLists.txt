cmake_minimum_required(VERSION 3.14)
project(yorg)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

# Avoid warning about DOWNLOAD_EXTRACT_TIMESTAMP in CMake 3.24:
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
  cmake_policy(SET CMP0135 NEW)
endif()

include(FetchContent)

# Google Test
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/58d77fa8070e8cec2dc1ed015d66b454c8d78850.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_library(ymicroservice
  src/capability.cpp
  src/service.cpp
)
target_include_directories(ymicroservice
  PUBLIC include
)

add_executable(ymicroservice_test
  test/service_test.cpp
)
target_link_libraries(ymicroservice_test
  ymicroservice
  GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(ymicroservice_test)
