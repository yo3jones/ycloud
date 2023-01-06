cmake_minimum_required(VERSION 3.14)
project(yutil)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

# Avoid warning about DOWNLOAD_EXTRACT_TIMESTAMP in CMake 3.24:
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
  cmake_policy(SET CMP0135 NEW)
endif()

include(FetchContent)

# Google Test
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_library(yutil
  src/env.cpp
  src/semaphore.cpp
  src/pool.h
)
target_include_directories(yutil
  PUBLIC include
)

add_executable(yutil_test
  test/semaphore_test.cpp
  test/pool_test.cpp
)
target_link_libraries(yutil_test
  yutil
  GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(yutil_test)
