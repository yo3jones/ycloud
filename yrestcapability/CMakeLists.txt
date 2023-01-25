cmake_minimum_required(VERSION 3.14)
project(yrestcapability)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

# Avoid warning about DOWNLOAD_EXTRACT_TIMESTAMP in CMake 3.24:
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
  cmake_policy(SET CMP0135 NEW)
endif()

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

FetchContent_Declare(
  curlpp
  URL https://github.com/jpbarrette/curlpp/archive/refs/tags/v0.8.1.zip
)
FetchContent_MakeAvailable(curlpp)

add_library(yrestcapability
  src/rest-capability.cpp

  src/validation/array-validator.cpp
  src/validation/number-validator.cpp
  src/validation/object-validator.cpp
  src/validation/pattern-validator.cpp
  src/validation/validation-constraint.cpp
  src/validation/validation-entry.cpp
  src/validation/validation-result.cpp
  src/validation/validator.cpp
  src/validation/validators.cpp
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

  test/validation/array-validator_test.cpp
  test/validation/number-validator_test.cpp
  test/validation/object-validator_test.cpp
  test/validation/validator_test.cpp
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
