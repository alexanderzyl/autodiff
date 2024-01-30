cmake_minimum_required(VERSION 3.27)
project(autodiff)

set(CMAKE_CXX_STANDARD 23)

# Include GoogleTest library
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.10.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Add test cpp file
add_executable(runTests
        tests/simple_tests.cpp)

target_link_libraries(runTests gtest gtest_main)
include_directories(include)