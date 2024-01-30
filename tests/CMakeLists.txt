include_directories(
        ${GTEST_ROOT}/googletest/include
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/include)

# Add the GTest library directory
link_directories(${GTEST_ROOT}/cmake-build-debug/lib)

add_executable(runTests
        test_differentiation.cpp
        test_algorithms.cpp
        test_polynomials.cpp
        test_taylor.cpp
        test_gradients.cpp
        )

target_link_libraries(runTests
        pthread GTest::GTest GTest::Main )
