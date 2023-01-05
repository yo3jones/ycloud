cmake_minimum_required(VERSION 3.14)
project(yorg)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

# Avoid warning about DOWNLOAD_EXTRACT_TIMESTAMP in CMake 3.24:
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
  cmake_policy(SET CMP0135 NEW)
endif()

include(FetchContent)

FetchContent_Declare(
  crow
  URL https://github.com/CrowCpp/Crow/archive/refs/tags/v1.0+5.zip
  # URL https://github.com/CrowCpp/Crow/releases/download/v1.0%2B5/crow-v1.0+5.tar.gz
  # requires asio
  # requires boost
)
FetchContent_MakeAvailable(crow)

# Google Test
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()

# add_executable(
#   yorg_test
#   src/db/db-connection-info.cpp
#   test/db/db-connection-info_test.cpp
# )
# target_link_libraries(
#   yorg_test
#   GTest::gtest_main
# )
#
# include(GoogleTest)
# gtest_discover_tests(yorg_test)

add_executable(yorg
  src/main.cpp

  src/controllers/hello-controller.cpp
)
target_link_libraries(yorg Crow::Crow)
# target_link_libraries(yorg "${PQXX_LIBRARIES}")

add_subdirectory(out/deps/ydb)
target_include_directories(yorg PUBLIC out/deps/ydb/include)
target_link_libraries(yorg
  ydb
)
