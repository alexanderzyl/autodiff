#include <gtest/gtest.h>
#include "fwddiff/taylor.h"
#include <fwddiff/uni>
#include <cmath>

class TaylorTest : public ::testing::Test {
    protected:
};

TEST_F(TaylorTest, exp_function) {
    constexpr auto taylor_exp = [](auto x) {
        return exp(x);
    };

    constexpr double value = 1.0;
    constexpr auto result_0 = algorithms::taylor<0>(taylor_exp, value, abstracts::zero{});
    // First term of the Taylor series
    // 1
    EXPECT_EQ(result_0, 1.0);

    constexpr auto result_1 = algorithms::taylor<1>(taylor_exp, value, abstracts::zero{});
    // First 2 terms of the Taylor series
    // 1 + x
    EXPECT_EQ(result_1, 2.0);

    constexpr auto result_2 = algorithms::taylor<2>(taylor_exp, value, abstracts::zero{});

    // First 3 terms of the Taylor series
    // 1 + x + x^2/2
    EXPECT_EQ(result_2, 2.5);

    constexpr auto result_3 = algorithms::taylor<3>(taylor_exp, value, abstracts::zero{});
    // First 4 terms of the Taylor series
    // 1 + x + x^2/2 + x^3/6
    EXPECT_EQ(result_3, 2.6666666666666665);

    constexpr auto result_10 = algorithms::taylor<10>(taylor_exp, value, abstracts::zero{});
    static_assert(result_10 != 0.0, "Static differentiation failed");
    EXPECT_NEAR(result_10, std::exp(1.0), 1e-6);
}

//TEST_F(TaylorTest, differentiate_sigmoid) {
//
//    constexpr auto sigmoid = [](auto x) {
//        return 1.0 / (1.0 + 1.0 + x + x*x/ 2.0 + x*x*x/6.0);
//    };
//
//    constexpr auto derivative = univariate::differentiate(sigmoid);
//    constexpr auto x = 1.0;
//    constexpr auto result = derivative(x);
//
//    static_assert(result != 0.0, "Static differentiation failed");
//    EXPECT_NEAR(result, 0.19661193324148185, 1e-6);
//}