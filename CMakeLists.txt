cmake_minimum_required(VERSION 3.27)
project(autodiff)

set(CMAKE_CXX_STANDARD 23)

set(GTEST_ROOT "/Users/aliaksandrzyl/Desktop/projects/googletest")
# Include GoogleTest library
find_package(GTest REQUIRED)

enable_testing()

add_subdirectory(tests)

#set(CMAKE_FIND_DEBUG_MODE TRUE)

list(APPEND CMAKE_PREFIX_PATH "/Users/aliaksandrzyl/Qt/6.6.1/macos")
# add subdirectory only when QT is found
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
if(Qt6Core_FOUND)
    add_subdirectory(visualization)
endif()