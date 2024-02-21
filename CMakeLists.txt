cmake_minimum_required(VERSION 3.27)
project(autodiff)

set(CMAKE_CXX_STANDARD 23)

if(NOT ${GTest_DIR} STREQUAL "")
    find_package(GTest REQUIRED)
    enable_testing()
    add_subdirectory(tests)
endif()


find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
if(Qt6Core_FOUND AND NOT ${GTest_DIR} STREQUAL "")
    add_subdirectory(visualization)
endif()