cmake_minimum_required(VERSION 3.14)
project(yutil)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

# Avoid warning about DOWNLOAD_EXTRACT_TIMESTAMP in CMake 3.24:
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
  cmake_policy(SET CMP0135 NEW)
endif()

find_package(Boost 1.80.0 REQUIRED)

include(FetchContent)

# Google Test
set(BUILD_GMOCK ON)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/58d77fa8070e8cec2dc1ed015d66b454c8d78850.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_library(yutil
  src/date-time.cpp
  src/env.cpp
  src/semaphore.cpp
  src/pool.h
  src/uuid.cpp
)
target_include_directories(yutil
  PUBLIC include
  PUBLIC ${Boost_INCLUDE_DIRS}
)

add_executable(yutil_test
  test/date-time_test.cpp
  test/semaphore_test.cpp
  test/pool_test.cpp
  test/uuid_test.cpp
)
target_link_libraries(yutil_test
  yutil
  gmock_main
  # GTest::gtest
)
include(GoogleTest)
gtest_discover_tests(yutil_test)
