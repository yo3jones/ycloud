cmake_minimum_required(VERSION 3.14)
project(ydbrestcapability)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

# Avoid warning about DOWNLOAD_EXTRACT_TIMESTAMP in CMake 3.24:
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
  cmake_policy(SET CMP0135 NEW)
endif()

find_package(Boost 1.80.0 REQUIRED)

include(FetchContent)

# Google Test
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/58d77fa8070e8cec2dc1ed015d66b454c8d78850.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_subdirectory(yutil)
add_subdirectory(ydb)
add_subdirectory(ymicroservice)
add_subdirectory(yrestcapability)
add_subdirectory(ydbcapability)
add_subdirectory(ydbrestcapability)
