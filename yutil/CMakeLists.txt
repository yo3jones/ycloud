cmake_minimum_required(VERSION 3.14)
project(yutil)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

add_library(yutil
  src/date-time.cpp
  src/env.cpp
  src/pool.h
  src/ro-type-map.cpp
  src/type-map.cpp
  src/uuid.cpp

  src/schema/array-schema.cpp
  src/schema/constraint.cpp
  src/schema/object-schema.cpp
  src/schema/schema.cpp
  src/schema/schemas.cpp
)
target_include_directories(yutil
  PUBLIC include
  PUBLIC ${Boost_INCLUDE_DIRS}
)

add_executable(yutil_test
  test/date-time_test.cpp
  test/pool_test.cpp
  test/type-map_test.cpp
  test/uuid_test.cpp

  test/schema/object-schema_test.cpp
  test/schema/schema_test.cpp
)
target_link_libraries(yutil_test
  yutil
  gmock_main
  # GTest::gtest
)
include(GoogleTest)
gtest_discover_tests(yutil_test)
