#include <gtest/gtest.h>
#include "taylor.h"
#include "abstracts_math.h"
#include "uni_math.h"
#include <cmath>

class TaylorTest : public ::testing::Test {
    protected:
};

TEST_F(TaylorTest, exp_function) {
    constexpr auto taylor_exp = [](auto x) {
        return exp(x);
    };

    double value = 1.0;
    auto result_0 = algorithms::taylor<0>(taylor_exp, value, abstracts::zero{});
    // First term of the Taylor series
    // 1
    EXPECT_EQ(result_0, 1.0);

    auto result_1 = algorithms::taylor<1>(taylor_exp, value, abstracts::zero{});
    // First 2 terms of the Taylor series
    // 1 + x
    EXPECT_EQ(result_1, 2.0);

    auto result_2 = algorithms::taylor<2>(taylor_exp, value, abstracts::zero{});

    // First 3 terms of the Taylor series
    // 1 + x + x^2/2
    EXPECT_EQ(result_2, 2.5);

    auto result_3 = algorithms::taylor<3>(taylor_exp, value, abstracts::zero{});
    // First 4 terms of the Taylor series
    // 1 + x + x^2/2 + x^3/6
    EXPECT_EQ(result_3, 2.6666666666666665);

    auto result_10 = algorithms::taylor<10>(taylor_exp, value, abstracts::zero{});
    EXPECT_NEAR(result_10, std::exp(1.0), 1e-6);
}