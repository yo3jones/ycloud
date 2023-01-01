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
  GIT_TAG a6b1d60e74c1427c8ac2324b85cd4a0dc2068332
)
set(PQXX_LIBRARIES pqxx_static)
FetchContent_MakeAvailable(libpqxx)

add_executable(
  ydb_test

  src/connection.cpp
  src/connection-info.cpp
  src/connection-info-builder.cpp
  src/result.cpp
  src/row.cpp
  src/reference.cpp

  src/driver/postgresql/postgresql-driver.cpp
  src/driver/postgresql/postgresql-driver-factory.cpp
  src/driver/postgresql/postgresql-result-driver.cpp
  src/driver/postgresql/postgresql-row-driver.cpp
  src/driver/postgresql/postgresql-reference-driver.cpp

  test/postgresql-test-environment.cpp
  test/test-setup.cpp

  test/connection-info_test.cpp
  test/connection-info-builder_test.cpp
  test/postgresql_test.cpp
)
target_link_libraries(
  ydb_test
  # GTest::gtest_main
  GTest::gtest
  "${PQXX_LIBRARIES}"
)
include(GoogleTest)
gtest_discover_tests(ydb_test)

add_library(ydb
  src/connection.cpp
  src/connection-info.cpp
  src/connection-info-builder.cpp
  src/result.cpp
  src/row.cpp
  src/reference.cpp

  src/driver/postgresql/postgresql-driver.cpp
  src/driver/postgresql/postgresql-driver-factory.cpp
  src/driver/postgresql/postgresql-result-driver.cpp
  src/driver/postgresql/postgresql-row-driver.cpp
  src/driver/postgresql/postgresql-reference-driver.cpp
)
target_link_libraries(ydb "${PQXX_LIBRARIES}")
