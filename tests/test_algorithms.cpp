#include <gtest/gtest.h>
#include "solvers.h"

class AlgorithmsTests : public ::testing::Test {
protected:
};



TEST_F(AlgorithmsTests, newton_square_root) {

    constexpr auto square_root_inv = [](auto x) {
        return x * x;
    };
    constexpr double value = 15.;

    auto result = solvers::newton(square_root_inv, value/2., value);


    EXPECT_NEAR(result, std::sqrt(value), 1e-7);
}