#include <gtest/gtest.h>
#include "multi_differentiate.h"
#include <tuple>

class TestGradients : public ::testing::Test {

};

TEST_F(TestGradients, test_simple) {
    auto func = [](auto x, auto y, auto z) {
        return x * y + z;
    };
    auto xyz1 = std::make_tuple(1.0, 2.0, 3.0);
    auto test_func = func(1.0, 2.0, 3.0);
    EXPECT_EQ(test_func, 5.0);
    auto grad = multivariate::differentiate<decltype(func), 3>(func);
    auto grad_x = grad.partial<0>();
    auto grad_y = grad.partial<1>();
    auto grad_z = grad.partial<2>();

    auto xyz1_dx = grad_x(xyz1);
    auto xyz1_dy = grad_y(xyz1);
    auto xyz1_dz = grad_z(xyz1);
    EXPECT_EQ(xyz1_dx, 2.0);
    EXPECT_EQ(xyz1_dy, 1.0);
    EXPECT_EQ(xyz1_dz, 1.0);
}