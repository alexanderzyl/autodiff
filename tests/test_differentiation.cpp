#include "uni_differentiate.h"
#include "polynomial.h"
#include "uni_math.h"
#include "uni_polynomial.h"

#include <gtest/gtest.h>

using namespace univariate;
namespace {
    constexpr double exp(double x) {
        return std::exp(x);
    }
}

class DifferentiationTests : public ::testing::Test {
protected:
};

TEST_F(DifferentiationTests, x_squared)
{
    constexpr auto f = [](auto x) {
        return x * x;
    };

    EXPECT_EQ(f(2.0), 4.0);
    EXPECT_EQ(differentiate_at(f, 2.0), 4.0);
    EXPECT_EQ(f(1.0), 1.0);
    EXPECT_EQ(differentiate_at(f, 1.0), 2.0);
}


TEST_F(DifferentiationTests, differntial) {
    constexpr auto lambda = [](auto x) {
        return 3.0 * x;
     };

    constexpr double value1 = 2.0;
    auto derivative1 = differentiate(lambda);
    auto d1 = derivative1(value1);
    EXPECT_EQ(d1, 3.0);
    constexpr auto static_result = static_differentiate_at(lambda, value1);
    EXPECT_EQ(static_result, 3.0);

    auto derivative2 = differentiate(derivative1);
    auto d2 = derivative2(value1);
    EXPECT_EQ(d2, 0.0);
}

TEST_F(DifferentiationTests, higer_order_differntials) {
    constexpr auto lambda = [](auto x) {
        return  -2.5*x*x*x + 2. * x * x +3.0 * x + 1.5;
    };

    constexpr double value = 1.0;
    constexpr auto result0 = lambda(value);
    EXPECT_EQ(result0, 4.0);
    constexpr auto result1 = differentiate_at(lambda, value);
    auto derivative1 = differentiate(lambda);
    EXPECT_EQ(result1, derivative1(value));
    EXPECT_EQ(result1, -0.5);

    auto derivative2 = differentiate(derivative1);
    EXPECT_EQ(derivative2(value), -11.0);

    auto derivative3 = differentiate(derivative2);
    EXPECT_EQ(derivative3(value), -15.0);

    auto derivative4 = differentiate(derivative3);
    EXPECT_EQ(derivative4(value), 0.0);

    auto derivative5 = differentiate(derivative4);
    EXPECT_EQ(derivative5(value), 0.0);
}

TEST_F(DifferentiationTests, sigmoid)
{
    auto sigmoid = [](auto x) {
        return 1.0 / (1.0 + exp(-x));
    };

    double value = 1.0;

    auto result = differentiate_at(sigmoid, value);
    EXPECT_NEAR(result, 0.196612, 0.000001);
}

TEST_F(DifferentiationTests, polynomial)
{
    using namespace polynomials;
    constexpr Polynomial function(1., 4., 3.);
    constexpr Polynomial derivative(4., 6.);

    constexpr double value = 1.0;
    constexpr auto result = differentiate_at(function, value);
    EXPECT_EQ(result, derivative(value));

    constexpr double value2 = 13.3;
    constexpr auto result2 = differentiate_at(function, value2);
    EXPECT_EQ(result2, derivative(value2));
    EXPECT_NEAR(result2, 83.8, 0.000001);

    constexpr double static_value = -2.3;
    constexpr auto static_result = static_differentiate_at(function, static_value);
    EXPECT_EQ(static_result, derivative(static_value));
}
