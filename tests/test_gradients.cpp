#include <gtest/gtest.h>
#include "multi_differentiate.h"

class TestGradients : public ::testing::Test {

};

TEST_F(TestGradients, test_simple) {
    auto func = [](auto x, auto y, auto z) {
        return x * y + z;
    };
    auto x = 1.0;
    auto y = 2.0;
    auto z = 3.0;
    auto test_func = func(x, y, z);
    EXPECT_EQ(test_func, 5.0);
    auto grad = multivariate::differentiate<decltype(func), 3>(func);
    auto grad_x = grad.partial<0>();
    auto grad_y = grad.partial<1>();
    auto grad_z = grad.partial<2>();

    auto xyz1_dx = grad_x(x, y, z);
    auto xyz1_dy = grad_y(x, y, z);
    auto xyz1_dz = grad_z(x, y, z);
    EXPECT_EQ(xyz1_dx, 2.0);
    EXPECT_EQ(xyz1_dy, 1.0);
    EXPECT_EQ(xyz1_dz, 1.0);
}

TEST_F(TestGradients, test_constants) {
    constexpr auto lambda = [](auto x, auto y) {
        return 3.0 * x - 2.0 * y * y * y + 1.5;
    };

    auto x = 1.0;
    auto y = 2.0;
    auto result = lambda(x, y);
    EXPECT_EQ(result, 3.0 - 16.0 + 1.5);

    auto grad = multivariate::differentiate<decltype(lambda), 2>(lambda);
    auto grad_x = grad.partial<0>();
    auto grad_y = grad.partial<1>();

    auto xy_dx = grad_x(x, y);
    auto xy_dy = grad_y(x, y);
    EXPECT_EQ(xy_dx, 3.0);
    EXPECT_EQ(xy_dy, -6.0 * y * y);
}