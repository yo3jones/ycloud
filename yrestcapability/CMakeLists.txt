cmake_minimum_required(VERSION 3.14)
project(yrestcapability)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

# Avoid warning about DOWNLOAD_EXTRACT_TIMESTAMP in CMake 3.24:
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
  cmake_policy(SET CMP0135 NEW)
endif()

add_subdirectory(
  ../ymicroservice
  ${CMAKE_CURRENT_BINARY_DIR}/ymicroservice
)
add_subdirectory(
  ../yutil
  ${CMAKE_CURRENT_BINARY_DIR}/yutil
)

include(FetchContent)

# Google Test
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/58d77fa8070e8cec2dc1ed015d66b454c8d78850.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()

FetchContent_Declare(
  crow
  URL https://github.com/CrowCpp/Crow/archive/refs/tags/v1.0+5.zip
  # URL https://github.com/CrowCpp/Crow/releases/download/v1.0%2B5/crow-v1.0+5.tar.gz
  # requires asio
  # requires boost
)
FetchContent_MakeAvailable(crow)

FetchContent_Declare(
  curlpp
  URL https://github.com/jpbarrette/curlpp/archive/refs/tags/v0.8.1.zip
)
FetchContent_MakeAvailable(curlpp)

add_library(yrestcapability
  src/rest-capability.cpp
)
target_include_directories(yrestcapability
  PUBLIC include
)
target_link_libraries(yrestcapability
  yutil
  ymicroservice
  Crow::Crow
)

add_library(yrestcapability_test
  test/rest-client.cpp
)
target_include_directories(yrestcapability_test
  PUBLIC test/include
)
target_link_libraries(yrestcapability_test
  yrestcapability
  curlpp
)
target_include_directories(yrestcapability_test
  PUBLIC ${curlpp_SOURCE_DIR}/include
)

add_executable(yrestcapability_test_test
  test/test-setup.cpp

  test/rest-capability_test.cpp
)
target_link_libraries(yrestcapability_test_test
  yrestcapability_test
  ymicroservice_test
  GTest::gtest
)
# target_include_directories(yrestcapability_test_test
#   PUBLIC ${curlpp_SOURCE_DIR}/include
# )
include(GoogleTest)
gtest_discover_tests(yrestcapability_test_test)
