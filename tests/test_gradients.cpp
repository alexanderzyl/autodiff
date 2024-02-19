#include <gtest/gtest.h>
#include "multi_differentiate.h"
#include "pow.h"
#include "multi_dual_math.h"
#include "functor_math.h"

class TestGradients : public ::testing::Test {

};

TEST_F(TestGradients, simple) {
    auto func = [](auto x, auto y, auto z) {
        return x * y + z;
    };
    auto x = 1.0;
    auto y = 2.0;
    auto z = 3.0;
    auto test_func = func(x, y, z);
    EXPECT_EQ(test_func, 5.0);
    auto grad = multivariate::differentiate<3>(func);
    auto grad_x = grad.function<0>();
    auto grad_y = grad.function<1>();
    auto grad_z = grad.function<2>();

    auto xyz1_dx = grad_x(x, y, z);
    auto xyz1_dy = grad_y(x, y, z);
    auto xyz1_dz = grad_z(x, y, z);
    EXPECT_EQ(xyz1_dx, 2.0);
    EXPECT_EQ(xyz1_dy, 1.0);
    EXPECT_EQ(xyz1_dz, 1.0);
}

TEST_F(TestGradients, simple2) {
    auto func = [](auto x, auto y, auto z) {
        return -1. * x * y + y;
    };

    auto x = 1.0;
    auto y = 2.0;
    auto z = 3.0;
    auto test_func = func(x, y, z);
    EXPECT_EQ(test_func, -2.0 + 2.0);

    auto grad = multivariate::differentiate<3>(func);
    auto grad_x = grad.function<0>();
    auto grad_y = grad.function<1>();
    auto grad_z = grad.function<2>();

    auto xyz2_dx = grad_x(x, y, z);
    auto xyz2_dy = grad_y(x, y, z);
    auto xyz2_dz = grad_z(x, y, z);

    EXPECT_EQ(xyz2_dx, -y + 0.0);
    EXPECT_EQ(xyz2_dy, -x + 1.0);
    EXPECT_EQ(xyz2_dz, 0.0);
}

TEST_F(TestGradients, constants) {
    constexpr auto lambda = [](auto x, auto y) {
        return 3.0 * x - 2.0 * y * y * y + 1.5;
    };

    auto x = 1.0;
    auto y = 2.0;
    auto result = lambda(x, y);
    EXPECT_EQ(result, 3.0 - 16.0 + 1.5);

    auto grad = multivariate::differentiate<2>(lambda);
    auto grad_x = grad.function<0>();
    auto grad_y = grad.function<1>();

    auto xy_dx = grad_x(x, y);
    auto xy_dy = grad_y(x, y);
    EXPECT_EQ(xy_dx, 3.0);
    EXPECT_EQ(xy_dy, -6.0 * y * y);
}

TEST_F(TestGradients, powers) {
    auto func = [](auto x, auto y) {
        return multivariate::pow<3>(x) + 2. * multivariate::pow<-1>(y);
    };

    auto x = -2.0;
    auto y = -3.0;

    auto test_func = func(x, y);
    EXPECT_EQ(test_func, -8.0 + 2.0 / (-3.0));

    auto grad = multivariate::differentiate<2>(func);

    auto grad_x = grad.function<0>();
    auto grad_y = grad.function<1>();

    auto xy_dx = grad_x(x, y);
    auto xy_dy = grad_y(x, y);

    EXPECT_EQ(xy_dx, 3.0 * x * x);
    EXPECT_EQ(xy_dy, -2.0 * multivariate::pow<-2>(y));
}

TEST_F(TestGradients, multivariate_powers)
{
    auto func = [](auto x, auto y) {
        return multivariate::pow<-2>(x) - multivariate::pow<3>(y * x + y);
    };

    auto x = 2.0;
    auto y = 3.0;

    auto test_func = func(x, y);
    EXPECT_EQ(test_func, 1./4. - multivariate::pow<3>(2. * 3. + 3.));

    auto grad = multivariate::differentiate<2>(func);

    auto grad_x = grad.function<0>();
    auto grad_y = grad.function<1>();

    auto xy_dx = grad_x(x, y);
    auto xy_dy = grad_y(x, y);

    EXPECT_EQ(xy_dx, -2.0 * multivariate::pow<-3>(x) - 3 * multivariate::pow<2>(y*x + y) * y);
    EXPECT_EQ(xy_dy, -3.0 * multivariate::pow<2>(y*x + y) * (x + 1));
}

TEST_F(TestGradients, division) {
    auto func = [](auto x, auto y) {
        return 3. * x / -(y*y);
    };
    auto x = 2.0;
    auto y = 3.0;
    auto test_func = func(x, y);
    EXPECT_NEAR(test_func, -2.0/3.0, 1e-7);
    auto grad = multivariate::differentiate<2>(func);
    auto grad_x = grad.function<0>();
    auto grad_y = grad.function<1>();

    auto xy_dx = grad_x(x, y);
    auto xy_dy = grad_y(x, y);

    EXPECT_NEAR(xy_dx, 3.0 / -(y*y), 1e-7);
    EXPECT_NEAR(xy_dy, 6.0 * x / (y*y*y), 1e-7);
}

TEST_F(TestGradients, sigmoid)
{
    constexpr auto sigmoid = [](auto x, auto offset, auto scale, auto max, auto min) {
        return (max - min) / (1.0 + exp(-scale * (x - offset))) + min;
    };

    constexpr auto offset = 1.0;
    constexpr auto scale = 2.0;
    constexpr auto max = 5.0;
    constexpr auto min = 0.0;
    constexpr auto x = 1.0;
    auto result = sigmoid(x, offset, scale, max, min);
    EXPECT_NEAR(result, 2.5, 1e-7);

    auto grad = multivariate::differentiate<5>(sigmoid);

    auto grad_x = grad.function<0>();
    auto grad_offset = grad.function<1>();
    auto grad_scale = grad.function<2>();
    auto grad_max = grad.function<3>();
    auto grad_min = grad.function<4>();

}