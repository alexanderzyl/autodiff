find_package(Qt6 REQUIRED COMPONENTS Widgets Charts)
qt_standard_project_setup()

include_directories(
        ../include
        ${GTEST_ROOT}/googletest/include
)

qt_add_executable(visualization
        ChartVisualizers.cpp
        differentials.cpp
        taylor.cpp
        solvers.cpp
        sigmoid.cpp
)

# Add the GTest library directory
link_directories(${GTEST_ROOT}/cmake-build-debug/lib)

# add this line for QApplication to be found
target_link_libraries(visualization
        PRIVATE
        Qt6::Core Qt6::Widgets Qt6::Charts
        pthread GTest::GTest GTest::Main )

set_target_properties(visualization PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
)