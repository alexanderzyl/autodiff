#include <gtest/gtest.h>
#include <fwddiff/solvers.h>

class AlgorithmsTests : public ::testing::Test {
protected:
};

TEST_F(AlgorithmsTests, newton_square_root) {

    constexpr auto square_root_inv = [](auto x) {
        return x * x;
    };
    constexpr double value = 15.;

    constexpr auto result = solvers::newton(square_root_inv, value/2., value);
    static_assert(result != 0.0, "Static differentiation failed");
    EXPECT_NEAR(result, std::sqrt(value), 1e-7);
}

TEST_F(AlgorithmsTests, newton_compute_pi) {
    constexpr auto arcsin_inv = [](auto x) {
        return univariate::sin(x);
    };

    auto result = solvers::newton(arcsin_inv, 2., 1., 1e-12, 1e6);
    EXPECT_NEAR(result, M_PI/ 2.0, 1e-6);
}