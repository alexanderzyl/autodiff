#include <gtest/gtest.h>
#include "pow.h"
#include "functor_math.h"
#include "multi_dual.h"
#include "multi_dual_math.h"
#include "multi_differentiate.h"

using namespace multivariate;

struct LaplacianTest : public ::testing::Test {

};

TEST_F(LaplacianTest, higher_order_derivatives) {
    constexpr auto lambda = [](auto x, auto y) {
        using namespace arithmetics;
        return  pow<3>(x) + 3. * x * y - 2. * pow<-1>(y);
    };

    auto gradient = differentiate<2>(lambda);
    auto dx = gradient.function<0>();
    auto dy = gradient.function<1>();

    auto ddx = differentiate<2>(gradient.partial<0>());
    auto ddy = differentiate<2>(gradient.partial<1>());

    auto ddxx = ddx.function<0>();
    auto ddxy = ddx.function<1>();
    auto ddyx = ddy.function<0>();
    auto ddyy = ddy.function<1>();

    double x = 1.;
    double y = 2.;

    auto ddxx_value = ddxx(x, y);
    EXPECT_EQ(ddxx_value, 6.);

    auto ddxy_value = ddxy(x, y);
    EXPECT_EQ(ddxy_value, 3.);

    auto ddyx_value = ddyx(x, y);
    EXPECT_EQ(ddyx_value, 3.);

    auto ddyy_value = ddyy(x, y);
    EXPECT_EQ(ddyy_value, -4 * pow<-3>(y));
}

TEST_F(LaplacianTest, sin_cos) {
    constexpr auto lambda = [](auto x, auto y) {
        using namespace arithmetics;
        return  sin(x) * cos(x*y);
    };

    auto x = 1.;
    auto y = 2;

    EXPECT_NEAR(lambda(x, y), std::sin(x) * std::cos(x * y), 1e-6);

    auto gradient = differentiate<2>(lambda);
    auto dx = gradient.function<0>();
    auto dy = gradient.function<1>();

    EXPECT_NEAR(dx(x, y), std::cos(x) * std::cos(x * y) - y * std::sin(x) * std::sin(x * y), 1e-6);
    EXPECT_NEAR(dy(x, y), -x * std::sin(x) * std::sin(x * y), 1e-6);

    auto ddx = differentiate<2>(gradient.partial<0>());
    auto ddy = differentiate<2>(gradient.partial<1>());

    auto ddxx = ddx.function<0>();
    auto ddxy = ddx.function<1>();
    auto ddyx = ddy.function<0>();
    auto ddyy = ddy.function<1>();

    EXPECT_NEAR(ddyy(x, y), -x * x * std::sin(x) * std::cos(x * y), 1e-6);
}