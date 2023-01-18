cmake_minimum_required(VERSION 3.14)
project(yorg)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

# Avoid warning about DOWNLOAD_EXTRACT_TIMESTAMP in CMake 3.24:
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
  cmake_policy(SET CMP0135 NEW)
endif()

add_library(yorg_lib
  src/service.cpp

  src/controllers/hello-controller.cpp
  src/controllers/tasks-controller.cpp

  src/migrations/2023-01-05T16-00-create-task.cpp
)
target_link_libraries(yorg_lib
  ydbrestcapability
)

add_executable(yorg_test
  test/test-setup.cpp

  test/tasks-controller_test.cpp
)
target_link_libraries(yorg_test
  yorg_lib
  ymicroservice_test
  yrestcapability_test
  # GTest::gtest_main
  # GTest::gtest
  gmock
)

include(GoogleTest)
gtest_discover_tests(yorg_test)

add_executable(yorg
  src/main.cpp
)
target_link_libraries(yorg yorg_lib)
