cmake_minimum_required(VERSION 3.14)
project(ydb)
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

FetchContent_Declare(
  libpqxx
  GIT_REPOSITORY https://github.com/jtv/libpqxx.git
  # 7.7.4
  GIT_TAG 17e5a6c8ac3abc05329891aaa378bd6004b9c8ee
)
set(PQXX_LIBRARIES pqxx)
FetchContent_MakeAvailable(libpqxx)

add_subdirectory(
  ../yutil
  ${CMAKE_CURRENT_BINARY_DIR}/yutil
)

add_library(ydb
  src/connection-info.cpp
  src/connection-info-builder.cpp
  src/connection-pool.cpp
  src/migration.cpp
  src/migrations-runner.cpp
  src/ydb.cpp
)
target_include_directories(ydb
  PUBLIC include
)
target_link_libraries(ydb
  "${PQXX_LIBRARIES}"
  yutil
)

add_library(ydb_test
  test/postgresql-test-environment.cpp
)
target_include_directories(ydb_test PUBLIC test/include)
target_link_libraries(ydb_test
  ydb
  # GTest::gtest_main
  GTest::gtest
)

add_executable(ydb_test_test
  test/test-setup.cpp

  test/connection-info_test.cpp
  test/connection-info-builder_test.cpp
  test/migrations_test.cpp
  test/connection-pool_test.cpp
)
target_link_libraries(ydb_test_test
  ydb
  ydb_test
)
include(GoogleTest)
gtest_discover_tests(ydb_test_test)
